foreach(name integer string vector array composition custom)
  ks_add_unit_test(test-serialization-${name}
    SOURCES
      test_serialization_${name}.cpp
    LIBS
      PRIVATE
        GTest::gtest_main
        ks-serialization
  )
endforeach()
