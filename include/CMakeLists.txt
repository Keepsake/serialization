include(GenerateExportHeader)
generate_export_header(ks-serialization
  EXPORT_FILE_NAME
    ks/serialization/detail/symbol_visibility.hpp
)

target_include_directories(
  ks-serialization
  PUBLIC
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(
  ks-serialization
  PUBLIC
    FILE_SET headers
      TYPE
        HEADERS
      BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
      FILES
        "${CMAKE_CURRENT_BINARY_DIR}/ks/serialization/detail/symbol_visibility.hpp"
        ks/serialization.hpp
        ks/serialization/archive.hpp
        ks/serialization/as_bytes.hpp
        ks/serialization/detail/serialize_range.hpp
        ks/serialization/error.hpp
        ks/serialization/serialize.hpp
        ks/serialization/std.hpp
)
