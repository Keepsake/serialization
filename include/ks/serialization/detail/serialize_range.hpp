#pragma once

#include <cstddef>

#include <ranges>
#include <span>
#include <type_traits>

#include <ks/serialization/archive.hpp>
#include <ks/serialization/serialize.hpp>

namespace ks::serialization::detail {

template<std::ranges::contiguous_range R>
constexpr void
serialize_range(oarchive& archive, R const& range) noexcept
{
  if constexpr (std::is_trivially_copyable_v<std::ranges::range_value_t<R>>)
    archive.save(std::as_bytes(std::span{ range }));
  else
    for (auto const& v : range)
      serialize(archive, v);
}

template<std::ranges::contiguous_range R>
constexpr void
serialize_range(iarchive& archive, R& range) noexcept
{
  if constexpr (std::is_trivially_copyable_v<std::ranges::range_value_t<R>>)
    archive.load(std::as_writable_bytes(std::span{ range }));
  else
    for (auto& v : range)
      serialize(archive, v);
}

template<std::ranges::contiguous_range R>
constexpr void
serialize_dynamic_range(oarchive& archive, R const& range) noexcept
{
  std::size_t const size = std::ranges::size(range);
  serialize(archive, size);
  serialize_range(archive, range);
}

template<std::ranges::contiguous_range R>
constexpr void
serialize_dynamic_range(iarchive& archive, R& range) noexcept
{
  std::size_t size;
  serialize(archive, size);
  range.resize(size);
  serialize_range(archive, range);
}

} // namespace ks::serialization::detail
