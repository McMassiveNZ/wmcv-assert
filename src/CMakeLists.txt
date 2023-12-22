set(current_target wmcv-assert)

add_library( ${current_target} "" )

target_sources(
    ${current_target} PRIVATE
    pch.h
    wmcv_assert.cpp
)

if(MSVC)
    target_sources(${current_target} PRIVATE pch.cpp)
endif()

target_precompile_headers(${current_target} PRIVATE pch.h pch.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

if( ENABLE_ALL_REASONABLE_WARNINGS )
    MESSAGE("-- Additional Warnings Enabled")
    target_enable_warnings(${current_target})
endif()

if( ENABLE_WARNINGS_AS_ERRORS )
    MESSAGE("-- Warnings as Errors")
    target_warnings_as_errors(${current_target})
endif()

if( ENABLE_SANITIZERS )
    MESSAGE("-- Sanitizers Enabled")
    target_enable_sanitizers(${current_target})
endif()

if( ENABLE_STATIC_ANALYSIS )
    MESSAGE("-- Static Analysis Enabled")
    target_enable_static_analysis(${current_target})
endif()
