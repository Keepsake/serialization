#include <system_error>

#include <gtest/gtest.h>

#include <ks/serialization.hpp>

namespace s = ks::serialization;

TEST(SerializationTest, CanPrintBufferUnderrunError)
{
  std::error_code const failure{ s::error::buffer_underrun };
  ASSERT_TRUE(failure);
  ASSERT_EQ("buffer underrun", failure.message());
  ASSERT_STREQ("serialization", failure.category().name());
}
