add_executable(
  bench-yas-serialization
  bench_yas_serialization.cpp
)

target_link_libraries(
  bench-yas-serialization
  PRIVATE
    benchmark::benchmark_main
)

target_compile_features(
  bench-yas-serialization
  PRIVATE 
    cxx_std_20
)

find_path(
  YAS_INCLUDE_DIRS
  "yas/serialize.hpp"
)

target_include_directories(
  bench-yas-serialization
  PRIVATE
    ${YAS_INCLUDE_DIRS}
)

add_executable(
  bench-ks-serialization
  bench_ks_serialization.cpp
)

target_link_libraries(
  bench-ks-serialization
  PRIVATE
    benchmark::benchmark_main
    ks-serialization
)

target_compile_features(
  bench-ks-serialization
  PRIVATE 
    cxx_std_20
)
