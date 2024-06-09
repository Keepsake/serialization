#pragma once

#include <array>
#include <ranges>

#include <ks/serialization/detail/namespace.hpp>
#include <ks/serialization/detail/serialize_range.hpp>
#include <ks/serialization/serialize.hpp>

KS_SERIALIZATION_NAMESPACE_BEGIN

template<std::ranges::contiguous_range R>
struct serializer<R> final
{
  constexpr void operator()(auto& archive, auto& range) const noexcept
  {
    detail::serialize_dynamic_range(archive, range);
  }
};

template<typename T, std::size_t N>
struct serializer<std::array<T, N>> final
{
  constexpr void operator()(auto& archive, auto& array) const noexcept
  {
    detail::serialize_range(archive, array);
  }
};

KS_SERIALIZATION_NAMESPACE_END
