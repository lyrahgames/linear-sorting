find_package(doctest REQUIRED)

add_executable(main-test
  doctest_main.cc
  counting_sort.cc
)

target_link_libraries(main-test
  PRIVATE
    doctest::doctest
    linear_sort::linear_sort
)

target_compile_features(main-test
  PRIVATE
    cxx_std_17
)

add_test(main-test main-test)