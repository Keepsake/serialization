if(KS_SERIALIZATION_BUILD_TEST)
  add_executable(ks-serialization-unit-test
    test_array.cpp
    test_composition.cpp
    test_custom.cpp
    test_integer.cpp
    test_string.cpp
    test_vector.cpp
    test_as_bytes.cpp
  )

  target_link_libraries(ks-serialization-unit-test
    PRIVATE
      GTest::gtest_main
      ${PROJECT_NAME}::ks-serialization
  )

  include(GoogleTest)
  gtest_discover_tests(ks-serialization-unit-test
    DISCOVERY_MODE
      PRE_TEST
    XML_OUTPUT_DIR
      reports
  )
endif()
