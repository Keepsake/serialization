#include <cstddef>

#include <variant>

#include <gtest/gtest.h>

#include <ks/serialization.hpp>

namespace s = ks::serialization;

TEST(SerializationTest, CanSerializeVariant)
{
  {
    std::variant<char, std::string> const expected{ 'C' };
    std::variant<char, std::string> actual;

    std::vector<std::byte> buffer;
    ASSERT_FALSE(s::save(buffer, expected));
    ASSERT_FALSE(s::load(buffer, actual));

    ASSERT_EQ(expected, actual);
  }
  {
    std::variant<char, std::string> const expected{ "string" };
    std::variant<char, std::string> actual;

    std::vector<std::byte> buffer;
    ASSERT_FALSE(s::save(buffer, expected));
    ASSERT_FALSE(s::load(buffer, actual));

    ASSERT_EQ(expected, actual);
  }
}
