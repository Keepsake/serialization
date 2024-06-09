#include <cstddef>

#include <array>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <ks/serialization.hpp>

namespace s = ks::serialization;

TEST(SerializationTest, CanSerializeArrayOfTrivialTypes)
{
  std::array<char, 8> const expected{ 'T', 'H', 'I', ' ', 'I', 'S', 'A', 'V' };
  std::array<char, 8> actual{};

  std::vector<std::byte> buffer;
  s::save(buffer, expected);
  s::load(buffer, actual);

  ASSERT_EQ(expected, actual);
}

TEST(SerializationTest, CanSerializeArrayOfNonTrivialTypes)
{
  std::array<std::string, 3> const expected{ "First", "Second", "Third" };
  std::array<std::string, 3> actual{};

  std::vector<std::byte> buffer;
  s::save(buffer, expected);
  s::load(buffer, actual);

  ASSERT_EQ(expected, actual);
}
