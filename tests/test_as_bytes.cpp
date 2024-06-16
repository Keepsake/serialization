#include <cstdint>

#include <array>

#include <gtest/gtest.h>

#include <ks/serialization.hpp>

namespace s = ks::serialization;

TEST(SerializationTest, CanCastSequenceAsBytes)
{
  std::array<char, 4U> const a{'a', 'b', 'c', 'd'};
  const auto a_s = s::as_bytes(a);

  ASSERT_EQ(a_s.size(), 4);
  ASSERT_EQ(a_s[0], std::byte{'a'});
  ASSERT_EQ(a_s[1], std::byte{'b'});
  ASSERT_EQ(a_s[2], std::byte{'c'});
  ASSERT_EQ(a_s[3], std::byte{'d'});
}

TEST(SerializationTest, CanCastSequenceAsWritableBytes)
{
  std::array<char, 4U> a{'a', 'b', 'c', 'd'};
  const auto a_s = s::as_writable_bytes(a);

  ASSERT_EQ(a_s.size(), 4);
  ASSERT_EQ(a_s[0], std::byte{'a'});
  ASSERT_EQ(a_s[1], std::byte{'b'});
  ASSERT_EQ(a_s[2], std::byte{'c'});
  ASSERT_EQ(a_s[3], std::byte{'d'});

  a_s[0] = std::byte{'1'};
  a_s[1] = std::byte{'2'};
  a_s[2] = std::byte{'3'};
  a_s[3] = std::byte{'4'};

  std::array<char, 4U> b{'1', '2', '3', '4'};
  ASSERT_EQ(a, b);
}
