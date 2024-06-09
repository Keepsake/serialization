#include <cstddef>

#include <array>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <ks/serialization.hpp>

namespace s = ks::serialization;

TEST(SerializationTest, CanSerializeCompositionOfSequences)
{
  using a = std::array<std::string, 4>;
  using b = std::array<a, 2>;
  using c = std::vector<b>;

  c const expected{
    {
        {
            "A",
            "B",
            "C",
            "D",
        },
        {
            "E",
            "F",
            "G",
            "H",
        },
    },
  };

  c actual{};

  std::vector<std::byte> buffer;
  s::save(buffer, expected);
  s::load(buffer, actual);

  ASSERT_EQ(expected, actual);
}
