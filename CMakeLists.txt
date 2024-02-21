cmake_minimum_required(VERSION 3.23)

project(KsSerialization LANGUAGES CXX)

option(BUILD_BENCHMARK "Enable benchmark build" ON)

find_package(KsCMakeHelpers CONFIG REQUIRED)
find_package(KsLog CONFIG REQUIRED)

ks_setup()

add_subdirectory(src)

if(BUILD_TESTING)
  find_package(GTest CONFIG REQUIRED)
  add_subdirectory(tests)
endif()

if(BUILD_BENCHMARK)
  find_package(benchmark CONFIG REQUIRED)
  add_subdirectory(benchmarks)
endif()
