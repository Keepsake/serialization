if(KS_SERIALIZATION_BUILD_BENCHMARK)
  add_executable(
    ks-serialization-bench-yas
    bench_yas_serialization.cpp
  )

  target_compile_features(
    ks-serialization-bench-yas
    PRIVATE
      cxx_std_23
  )

  target_link_libraries(
    ks-serialization-bench-yas
    PRIVATE
      benchmark::benchmark_main
      Yas::yas
  )

  add_executable(
    ks-serialization-bench-ks
    bench_ks_serialization.cpp
  )

  target_link_libraries(
    ks-serialization-bench-ks
    PRIVATE
      benchmark::benchmark_main
      ${PROJECT_NAME}::ks-serialization
  )
endif()
