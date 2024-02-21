#pragma once

#include <cstdint>

#include <array>
#include <string>
#include <vector>

struct my_struct final
{
  std::uint64_t unsigned_integer;
  std::int64_t signed_integer;
  std::string string;
  std::vector<std::string> strings_vector;
  std::array<std::string, 3> strings_array;

  bool operator!=(my_struct const&) const noexcept = default;
  bool operator==(my_struct const&) const noexcept = default;
};
