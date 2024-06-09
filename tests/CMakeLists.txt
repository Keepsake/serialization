find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(test-serialization
  test_array.cpp
  test_composition.cpp
  test_custom.cpp
  test_integer.cpp
  test_string.cpp
  test_vector.cpp
  test_as_bytes.cpp
)

target_link_libraries(test-serialization
  PRIVATE
    GTest::gtest_main
    ks-serialization
)

gtest_discover_tests(test-serialization
  DISCOVERY_MODE
    PRE_TEST
  XML_OUTPUT_DIR
    reports
)
