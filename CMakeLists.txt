cmake_minimum_required(VERSION 3.10)
project(linear-sorting VERSION 0.1.0 LANGUAGES CXX)
enable_testing()

find_package(doctest REQUIRED)

add_executable(main-test
  doctest_main.cc
  counting_sort.cc
)

target_link_libraries(main-test
  PRIVATE
    doctest::doctest
)

target_compile_features(main-test
  PRIVATE
    cxx_std_17
)

add_test(main-test main-test)