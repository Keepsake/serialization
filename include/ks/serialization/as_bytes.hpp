#pragma once

#include <ranges>
#include <span>
#include <type_traits>

namespace ks::serialization {
inline namespace abiv1 {

template<std::ranges::contiguous_range R>
constexpr auto
as_bytes(R const& range)
{
  static_assert(std::is_trivially_copyable_v<std::ranges::range_value_t<R>>,
                "range elements must be trivially copyable");
  return std::as_bytes(std::span{ range });
}

template<std::ranges::contiguous_range R>
constexpr auto
as_writable_bytes(R& range)
{
  static_assert(std::is_trivially_copyable_v<std::ranges::range_value_t<R>>,
                "range elements must be trivially copyable");
  return std::as_writable_bytes(std::span{ range });
}

} // namespace abiv1
} // namespace ks::serialization
