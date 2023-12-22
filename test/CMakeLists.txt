include(gtest)

add_executable(
  wmcv-assert-test
  test_main.cpp
)

target_link_libraries(
  wmcv-assert-test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(wmcv-assert-test)
