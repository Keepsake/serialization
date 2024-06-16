file(
  CONFIGURE
  OUTPUT namespace.hpp
  CONTENT [[
#define KS_SERIALIZATION_NAMESPACE_BEGIN namespace ks::serialization { inline namespace abi@PROJECT_VERSION_MAJOR@ {
#define KS_SERIALIZATION_NAMESPACE_END }}
]])
