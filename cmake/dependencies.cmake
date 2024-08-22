# SPDX-License-Identifier: MIT

set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)

find_package(KsCMakeHelpers 3.0.0 CONFIG REQUIRED)

find_package(KsFatal 1.1.1 CONFIG REQUIRED)

if(KS_SERIALIZATION_BUILD_TEST)
  find_package(GTest 1.15.0 CONFIG REQUIRED)
endif()

if(KS_SERIALIZATION_BUILD_BENCHMARK)
  find_package(benchmark 1.8.5 CONFIG REQUIRED)

  find_path(
    YAS_INCLUDE_DIRS
    "yas/serialize.hpp"
  )
  add_library(yas INTERFACE)
  add_library(Yas::yas ALIAS yas)
  target_include_directories(yas INTERFACE ${YAS_INCLUDE_DIRS})
endif()
