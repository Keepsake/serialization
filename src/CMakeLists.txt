add_library(ks-serialization INTERFACE)

target_include_directories(
  ks-serialization
  INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_sources(
  ks-serialization
  INTERFACE
    FILE_SET headers
      TYPE
        HEADERS
      BASE_DIRS
        ${PROJECT_BINARY_DIR}/include/
        ${PROJECT_SOURCE_DIR}/include/
      FILES
        ${PROJECT_SOURCE_DIR}/include/ks/serialization.hpp
        ${PROJECT_SOURCE_DIR}/include/ks/serialization/archive.hpp
        ${PROJECT_SOURCE_DIR}/include/ks/serialization/detail/serialize_range.hpp
        ${PROJECT_BINARY_DIR}/include/ks/serialization/detail/namespace.hpp
        ${PROJECT_SOURCE_DIR}/include/ks/serialization/serialize.hpp
        ${PROJECT_SOURCE_DIR}/include/ks/serialization/std.hpp
)

target_link_libraries(
  ks-serialization
  INTERFACE
    KsLog::ks-log
)

ks_install(
  TARGETS
    ks-serialization
  DEPENDENCIES
    KsLog
)
