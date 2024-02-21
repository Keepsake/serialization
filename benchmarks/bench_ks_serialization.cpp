#include <cstdint>

#include <array>
#include <string>
#include <vector>

#include <benchmark/benchmark.h>

#include <ks/serialization.hpp>

#include "serialization_struct.hpp"

template<>
struct ks::serialization::serializer<my_struct> final
{
  constexpr void operator()(auto& archive, auto& value) const noexcept
  {
    serialize(archive,
              value.unsigned_integer,
              value.signed_integer,
              value.string,
              value.strings_vector,
              value.strings_array);
  }
};

void
bench_ks(benchmark::State& state)
{
  my_struct const origin{ .unsigned_integer = 26ULL,
                          .signed_integer = -46738948LL,
                          .string{ "this is a normal" },
                          .strings_vector{
                              "first",
                              "second",
                              "third",
                          },
                          .strings_array{
                              "afirst",
                              "asecond",
                              "athird",
                          } };
  my_struct actual;

  std::vector<std::byte> buffer;

  for (auto _ : state) {
    buffer.clear();

    ks::serialization::save(buffer, origin);
    ks::serialization::load(buffer, actual);
  }

  if (actual != origin)
    throw std::runtime_error{ "Failed to serialize" };
}

BENCHMARK(bench_ks);

BENCHMARK_MAIN();
