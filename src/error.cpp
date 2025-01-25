#include <ks/serialization/error.hpp>

#include <string>

namespace ks::serialization {
inline namespace abiv1 {

namespace {

class category final : public std::error_category
{
public:
  char const* name() const noexcept override { return "serialization"; }

  std::string message(int condition) const override
  {
    switch (static_cast<error>(condition)) {
      case error::buffer_underrun:
        return "buffer underrun";
    }

    return "unknown error";
  }
};

} // namespace

std::error_category const&
serialization_category()
{
  static category category_{};
  return category_;
}

} // namespace abiv1
} // namespace ks::serialization
