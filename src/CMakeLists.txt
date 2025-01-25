add_library(ks-serialization
  error.cpp
)

target_compile_features(ks-serialization
  PUBLIC
    cxx_std_23
)

add_library(${PROJECT_NAME}::ks-serialization ALIAS ks-serialization)
