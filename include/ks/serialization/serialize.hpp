#pragma once

#include <cstddef>

#include <ranges>
#include <span>
#include <system_error>
#include <type_traits>
#include <vector>

#include <ks/serialization/archive.hpp>

namespace ks::serialization {
inline namespace abiv1 {

template<typename T>
struct serializer final
{
  std::error_code operator()(oarchive& archive, T const& object) const noexcept
  {
    static_assert(std::is_trivially_copyable_v<T>,
                  "missing ks::serialization::serializer<> specialization");
    return archive.save(std::as_bytes(std::span<T const, 1U>{ &object, 1U }));
  }

  std::error_code operator()(iarchive& archive, T& object) const noexcept
  {
    static_assert(std::is_trivially_copyable_v<T>,
                  "missing ks::serialization::serializer<> specialization");
    return archive.load(
        std::as_writable_bytes(std::span<T, 1U>{ &object, 1U }));
  }
};

template<typename Arg, typename... Args>
std::error_code
serialize(auto& archive, Arg& value, Args&... values) noexcept
{
  if (auto failure = serializer<std::decay_t<Arg>>{}(archive, value); failure)
      [[unlikely]]
    return failure;

  return serialize(archive, values...);
}

template<typename Arg>
std::error_code
serialize(auto& archive, Arg& value) noexcept
{
  return serializer<std::decay_t<Arg>>{}(archive, value);
}

std::error_code
save(std::vector<std::byte>& buffer, auto const& object) noexcept
{
  oarchive out{ buffer };
  return serialize(out, object);
}

std::error_code
load(std::span<std::byte const> buffer, auto& object) noexcept
{
  iarchive in{ buffer };
  return serialize(in, object);
}

} // namespace abiv1
} // namespace ks::serialization
