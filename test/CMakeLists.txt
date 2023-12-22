include(gtest)

set(current_target wmcv-assert-test)

add_executable(
  ${current_target}
  test_wmcv_assert.cpp
  pch.h
)

target_link_libraries(
  ${current_target}
  wmcv-assert
  gtest_main
  gmock_main
)

if(MSVC)
    target_sources(${current_target} PRIVATE pch.cpp)
endif()

target_precompile_headers(${current_target} PRIVATE pch.h pch.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

include(GoogleTest)
gtest_discover_tests(${current_target})
