#ifndef WMCV_ASSERT_PCH_H_INCLUDED
#define WMCV_ASSERT_PCH_H_INCLUDED

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef NOMINMAX
#endif

#include <version>

#if __cpp_lib_source_location
#include <source_location>
#endif

#include <array>
#include <cinttypes>
#include <cstddef>
#include <cstdio>
#include <string_view>

#endif //WMCV_ASSERT_PCH_H_INCLUDED
