#pragma once

#include <cstddef>

#include <algorithm>
#include <iterator>
#include <span>
#include <system_error>
#include <vector>

#include <ks/serialization/error.hpp>

namespace ks::serialization {
inline namespace abiv1 {

class oarchive final
{
public:
  using data_type = std::vector<std::byte>;

public:
  constexpr oarchive(data_type& data) noexcept
    : data_(data)
  {
  }

  template<std::size_t N>
  std::error_code save(std::span<std::byte const, N> bytes) noexcept
  {
    data_.insert(data_.end(), bytes.begin(), bytes.end());
    return {};
  }

private:
  data_type& data_;
};

class iarchive final
{
public:
  using data_type = std::span<std::byte const>;

public:
  constexpr iarchive(data_type data) noexcept
    : begin_(data.begin())
    , end_(data.end())
  {
  }

  template<std::size_t N>
  std::error_code load(std::span<std::byte, N> bytes) noexcept
  {
    if (bytes.size() > std::distance(begin_, end_)) [[unlikely]]
      return error::buffer_underrun;

    std::copy_n(begin_, bytes.size(), bytes.begin());
    std::advance(begin_, bytes.size());
    return {};
  }

private:
  data_type::iterator begin_;
  data_type::iterator end_;
};

} // namespace abiv1
} // namespace ks::serialization
