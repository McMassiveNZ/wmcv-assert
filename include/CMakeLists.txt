set(current_target wmcv-assert)

target_sources(
    ${current_target}
        PRIVATE
            wmcv_assert/wmcv_assert.h
)

target_include_directories(
    ${current_target}
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/wmcv_assert
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
)