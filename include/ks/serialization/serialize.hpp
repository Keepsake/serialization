#pragma once

#include <cstddef>

#include <ranges>
#include <span>
#include <type_traits>
#include <vector>

#include <ks/serialization/archive.hpp>

namespace ks::serialization {

template<typename T>
struct serializer final
{
  constexpr void operator()(oarchive& archive, T const& object) const noexcept
  {
    static_assert(std::is_trivially_copyable_v<T>,
                  "missing ks::serialization::serializer<> specialization");
    archive.save(std::as_bytes(std::span<T const, 1U>{ &object, 1U }));
  }

  constexpr void operator()(iarchive& archive, T& object) const noexcept
  {
    static_assert(std::is_trivially_copyable_v<T>,
                  "missing ks::serialization::serializer<> specialization");
    archive.load(std::as_writable_bytes(std::span<T, 1U>{ &object, 1U }));
  }
};

template<typename... Args>
constexpr void
serialize(auto& archive, Args&... value) noexcept
{
  (serializer<std::decay_t<Args>>{}(archive, value), ...);
}

constexpr void
save(std::vector<std::byte>& buffer, auto const& object) noexcept
{
  oarchive out{ buffer };
  serialize(out, object);
}

constexpr void
load(std::span<std::byte const> buffer, auto& object) noexcept
{
  iarchive in{ buffer };
  serialize(in, object);
}

} // namespace ks::serialization
