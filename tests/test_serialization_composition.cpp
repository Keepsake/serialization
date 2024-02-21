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
    b{
        a{
            "A",
            "B",
            "C",
            "D",
        },
        a{
            "E",
            "F",
            "G",
            "H",
        },
    },
    b{
        a{
            "I",
            "J",
            "K",
            "L",
        },
        a{
            "M",
            "N",
            "O",
            "P",
        },
    },
    b{
        a{
            "Q",
            "R",
            "S",
            "T",
        },
        a{
            "U",
            "V",
            "W",
            "X",
        },
    },
  };

  c actual{};

  std::vector<std::byte> buffer;
  s::save(buffer, expected);
  s::load(buffer, actual);

  ASSERT_EQ(expected, actual);
}
