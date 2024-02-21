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
        ${PROJECT_SOURCE_DIR}/include/
      FILES
        ${PROJECT_SOURCE_DIR}/include/ks/serialization.hpp
        ${PROJECT_SOURCE_DIR}/include/ks/serialization/archive.hpp
        ${PROJECT_SOURCE_DIR}/include/ks/serialization/detail/serialize_range.hpp
        ${PROJECT_SOURCE_DIR}/include/ks/serialization/serialize.hpp
        ${PROJECT_SOURCE_DIR}/include/ks/serialization/std.hpp
)

target_link_libraries(
  ks-serialization
  INTERFACE
    KsLog::ks-log
)

target_compile_features(
  ks-serialization
  INTERFACE
    cxx_std_20
)

ks_install(
  TARGETS
    ks-serialization
  DEPENDENCIES
    KsLog
)

