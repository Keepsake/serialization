#include <cstddef>
#include <cstdint>

#include <array>
#include <string>
#include <vector>

#include <benchmark/benchmark.h>

#include <yas/mem_streams.hpp>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

#include "serialization_struct.hpp"

template<typename Ar>
void
serialize(Ar& ar, my_struct& s)
{
  ar(s.unsigned_integer,
     s.signed_integer,
     s.string,
     s.strings_vector,
     s.strings_array);
}

template<typename Ar>
struct yas::detail::serialization_method<my_struct, Ar>
{
  static constexpr ser_case value = ser_case::has_one_function;
};

void
bench_yas(benchmark::State& state)
{
  my_struct const origin{
    .unsigned_integer = 26ULL,
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
    },
  };
  my_struct actual;

  std::vector<std::uint8_t> buffer;

  static constexpr auto flags = yas::mem | yas::binary;

  for (auto _ : state) {
    buffer.clear();
    yas::vector_ostream<std::uint8_t> out{ buffer };
    yas::save<flags>(std::move(out), origin);

    yas::load<flags>(buffer, actual);
  }

  if (actual != origin)
    throw std::runtime_error{ "Failed to serialize" };
}

BENCHMARK(bench_yas);

BENCHMARK_MAIN();
