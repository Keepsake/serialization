#include <cstddef>

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <ks/serialization.hpp>

namespace s = ks::serialization;

TEST(SerializationTest, CanSerializeVectorOfTrivialTypes)
{
  std::vector<char> const expected{ 'T', 'H', 'I', ' ', 'I', 'S', 'A', 'V' };
  std::vector<char> actual{};

  std::vector<std::byte> buffer;
  ASSERT_FALSE(s::save(buffer, expected));
  ASSERT_FALSE(s::load(buffer, actual));

  ASSERT_EQ(expected, actual);
}

TEST(SerializationTest, CanSerializeVectorOfNonTrivialTypes)
{
  std::vector<std::string> const expected{ "First", "Second", "Third" };
  std::vector<std::string> actual{};

  std::vector<std::byte> buffer;
  ASSERT_FALSE(s::save(buffer, expected));
  ASSERT_FALSE(s::load(buffer, actual));

  ASSERT_EQ(expected, actual);
}
