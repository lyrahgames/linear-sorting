cmake_minimum_required(VERSION 3.10)
project(linear-sorting VERSION 0.1.0 LANGUAGES CXX)
enable_testing()

add_library(linear_sort INTERFACE)

target_compile_features(linear_sort
  INTERFACE
    cxx_std_17
)

target_include_directories(linear_sort
  INTERFACE
    .
)

add_library(linear_sort::linear_sort ALIAS linear_sort)

add_subdirectory(tests)