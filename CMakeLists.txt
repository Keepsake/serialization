cmake_minimum_required(VERSION 3.23)

project(KsSerialization VERSION 1 LANGUAGES CXX)

option(BUILD_BENCHMARK "Enable benchmark build" ON)

find_package(KsCMakeHelpers CONFIG REQUIRED)
find_package(KsLog CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ks_setup()

add_subdirectory(src)
add_subdirectory(include)

if(BUILD_TESTING)
  find_package(GTest CONFIG REQUIRED)
  add_subdirectory(tests)
endif()

if(BUILD_BENCHMARK)
  find_package(benchmark CONFIG REQUIRED)
  add_subdirectory(benchmarks)
endif()
