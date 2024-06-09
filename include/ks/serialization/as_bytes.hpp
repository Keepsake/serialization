#pragma once

#include <ranges>
#include <span>
#include <type_traits>

#include <ks/serialization/detail/namespace.hpp>

KS_SERIALIZATION_NAMESPACE_BEGIN

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

KS_SERIALIZATION_NAMESPACE_END
