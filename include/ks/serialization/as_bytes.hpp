#pragma once

#include <ranges>
#include <span>
#include <type_traits>

namespace ks::serialization {
inline namespace abiv1 {

template<typename R>
concept trivially_serializable_range =
    std::ranges::contiguous_range<R> and
    std::is_trivially_copyable_v<std::ranges::range_value_t<R>>;

constexpr auto
as_bytes(trivially_serializable_range auto const& range) noexcept
{
  return std::as_bytes(std::span{ range });
}

constexpr auto
as_writable_bytes(trivially_serializable_range auto& range) noexcept
{
  return std::as_writable_bytes(std::span{ range });
}

} // namespace abiv1
} // namespace ks::serialization
