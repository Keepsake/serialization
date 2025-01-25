#pragma once

#include <system_error>
#include <type_traits>

#include <ks/serialization/detail/symbol_visibility.hpp>

namespace ks::serialization {
inline namespace abiv1 {

enum class error
{
  buffer_underrun = 1,
};

KS_SERIALIZATION_EXPORT std::error_category const&
serialization_category();

inline std::error_code
make_error_code(error error) noexcept
{
  return { static_cast<int>(error), serialization_category() };
}

} // namespace abiv1
} // namespace ks::serialization

template<>
struct std::is_error_code_enum<ks::serialization::error> : std::true_type
{};
