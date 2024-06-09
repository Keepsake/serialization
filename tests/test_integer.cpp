#include <cstddef>
#include <cstdint>

#include <vector>

#include <gtest/gtest.h>

#include <ks/serialization.hpp>

namespace s = ks::serialization;

TEST(SerializationTest, CanSerializeUnsignedInteger)
{
  {
    std::uint8_t const expected{ 42 };
    std::uint8_t actual{};

    std::vector<std::byte> buffer;
    s::save(buffer, expected);
    s::load(buffer, actual);

    ASSERT_EQ(buffer.size(), sizeof(expected));
    ASSERT_EQ(expected, actual);
  }
  {
    std::uint16_t const expected{ 42 };
    std::uint16_t actual{};

    std::vector<std::byte> buffer;
    s::save(buffer, expected);
    s::load(buffer, actual);

    ASSERT_EQ(buffer.size(), sizeof(expected));
    ASSERT_EQ(expected, actual);
  }
  {
    std::uint32_t const expected{ 42 };
    std::uint32_t actual{};

    std::vector<std::byte> buffer;
    s::save(buffer, expected);
    s::load(buffer, actual);

    ASSERT_EQ(buffer.size(), sizeof(expected));
    ASSERT_EQ(expected, actual);
  }
  {
    std::uint64_t const expected{ 42 };
    std::uint64_t actual{};

    std::vector<std::byte> buffer;
    s::save(buffer, expected);
    s::load(buffer, actual);

    ASSERT_EQ(buffer.size(), sizeof(expected));
    ASSERT_EQ(expected, actual);
  }
}

TEST(SerializationTest, CanSerializeSignedInteger)
{
  {
    std::int8_t const expected{ 42 };
    std::int8_t actual{};

    std::vector<std::byte> buffer;
    s::save(buffer, expected);
    s::load(buffer, actual);

    ASSERT_EQ(buffer.size(), sizeof(expected));
    ASSERT_EQ(expected, actual);
  }
  {
    std::int16_t const expected{ 42 };
    std::int16_t actual{};

    std::vector<std::byte> buffer;
    s::save(buffer, expected);
    s::load(buffer, actual);

    ASSERT_EQ(buffer.size(), sizeof(expected));
    ASSERT_EQ(expected, actual);
  }
  {
    std::int32_t const expected{ 42 };
    std::int32_t actual{};

    std::vector<std::byte> buffer;
    s::save(buffer, expected);
    s::load(buffer, actual);

    ASSERT_EQ(buffer.size(), sizeof(expected));
    ASSERT_EQ(expected, actual);
  }
  {
    std::int64_t const expected{ 42 };
    std::int64_t actual{};

    std::vector<std::byte> buffer;
    s::save(buffer, expected);
    s::load(buffer, actual);

    ASSERT_EQ(buffer.size(), sizeof(expected));
    ASSERT_EQ(expected, actual);
  }
}

TEST(SerializationTest, CanDetectCorruptedArchive)
{
  std::int8_t actual{};

  std::vector<std::byte> buffer;
  ASSERT_DEATH(s::load(buffer, actual), "deserialization buffer underrun");
}
