#pragma once

#include <cstddef>

#include <ranges>

#include <ks/serialization/archive.hpp>
#include <ks/serialization/as_bytes.hpp>
#include <ks/serialization/serialize.hpp>

namespace ks::serialization {
inline namespace abiv1 {
namespace detail {

std::error_code
serialize_range(oarchive& archive,
                trivially_serializable_range auto const& range)
{
  return archive.save(as_bytes(range));
}

std::error_code
serialize_range(iarchive& archive, trivially_serializable_range auto& range)
{
  return archive.load(as_writable_bytes(range));
}

std::error_code
serialize_range(oarchive& archive, std::ranges::range auto const& range)
{
  for (auto const& v : range)
    if (auto failure = serialize(archive, v); failure) [[unlikely]]
      return failure;

  return {};
}

std::error_code
serialize_range(iarchive& archive, std::ranges::range auto& range)
{
  for (auto& v : range)
    if (auto failure = serialize(archive, v); failure)
      return failure;

  return {};
}

std::error_code
serialize_dynamic_range(oarchive& archive, std::ranges::range auto const& range)
{
  std::size_t const size = std::ranges::size(range);
  if (auto failure = serialize(archive, size); failure)
    return failure;

  return serialize_range(archive, range);
}

std::error_code
serialize_dynamic_range(iarchive& archive, std::ranges::range auto& range)
{
  std::size_t size;
  if (auto failure = serialize(archive, size); failure)
    return failure;

  range.resize(size);
  return serialize_range(archive, range);
}

} // namespace detail
} // namespace abiv1
} // namespace ks::serialization
