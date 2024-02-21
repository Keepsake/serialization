#pragma once

#include <cstddef>

#include <algorithm>
#include <array>
#include <iterator>
#include <span>
#include <vector>

#include <ks/log.hpp>

namespace ks::serialization {

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
  constexpr void save(std::span<std::byte const, N> bytes) noexcept
  {
    data_.insert(data_.end(), bytes.begin(), bytes.end());
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
  constexpr void load(std::span<std::byte, N> bytes) noexcept
  {
    if (bytes.size() > std::distance(begin_, end_)) [[unlikely]]
      log::fatal("deserialization buffer underrun");

    std::copy_n(begin_, bytes.size(), bytes.begin());
    std::advance(begin_, bytes.size());
  }

private:
  data_type::iterator begin_;
  data_type::iterator end_;
};

} // namespace ks::serialization
