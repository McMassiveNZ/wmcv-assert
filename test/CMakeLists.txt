include(gtest)

set(current_target wmcv-assert-test)

add_executable(
  ${current_target}
  test_main.cpp
)

target_link_libraries(
  ${current_target}
  wmcv-assert
  gtest_main
  gmock_main
)

include(GoogleTest)
gtest_discover_tests(${current_target})
