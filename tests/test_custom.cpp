#include <cstddef>

#include <array>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <ks/serialization.hpp>

namespace s = ks::serialization;

struct type_1 final
{
  std::uint32_t a;
  std::string b;

  bool operator!=(type_1 const&) const noexcept = default;
  bool operator==(type_1 const&) const noexcept = default;
};

template<>
struct s::serializer<type_1> final
{
  constexpr void operator()(auto& archive, auto& v) const noexcept
  {
    serialize(archive, v.a, v.b);
  }
};

struct type_2 final
{
  type_1 a;
  std::int32_t b;

  bool operator!=(type_2 const&) const noexcept = default;
  bool operator==(type_2 const&) const noexcept = default;
};

template<>
struct s::serializer<type_2> final
{
  constexpr void operator()(auto& archive, auto& v) const noexcept
  {
    serialize(archive, v.a, v.b);
  }
};

TEST(SerializationTest, CanSerializeCustom)
{
  type_2 const expected{
    .a{
        .a = 42U,
        .b = "string",
    },
    .b = -42,
  };

  type_2 actual{};

  std::vector<std::byte> buffer;
  s::save(buffer, expected);
  s::load(buffer, actual);

  ASSERT_EQ(expected, actual);
}
