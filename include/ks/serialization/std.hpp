#pragma once

#include <array>
#include <cstdint>
#include <limits>
#include <ranges>
#include <variant>

#include <ks/serialization/detail/serialize_range.hpp>
#include <ks/serialization/serialize.hpp>

namespace ks::serialization {
inline namespace abiv1 {

template<std::ranges::range R>
struct serializer<R> final
{
  std::error_code operator()(auto& archive, auto& range) const
  {
    return detail::serialize_dynamic_range(archive, range);
  }
};

template<typename T, std::size_t N>
struct serializer<std::array<T, N>> final
{
  std::error_code operator()(auto& archive, auto& array) const
  {
    return detail::serialize_range(archive, array);
  }
};

template<typename... Ts>
struct serializer<std::variant<Ts...>> final
{
public:
  std::error_code operator()(oarchive& archive, auto const& variant) const
  {
    return std::visit(
        [&](auto const& value) {
          index_type const index = variant.index();
          return serialize(archive, index, value);
        },
        variant);
  }

  std::error_code operator()(iarchive& archive, auto& variant) const
  {
    index_type index;
    if (auto failure = serialize(archive, index); failure) [[unlikely]]
      return failure;

    static constexpr std::array loaders{ load<Ts>... };
    return loaders[index](archive, variant);
  }

private:
  using index_type = std::uint8_t;
  static_assert(sizeof...(Ts) <= std::numeric_limits<index_type>::max());

private:
  template<typename T>
  static std::error_code load(iarchive& archive, std::variant<Ts...>& variant)
  {
    return serialize(archive, variant.template emplace<T>());
  }
};

} // namespace abiv1
} // namespace ks::serialization
