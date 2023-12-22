#include "pch.h"
#include "wmcv_assert/wmcv_assert.h"

namespace wmcv
{

#if defined(__GNUC__)
#define WMCV_DEBUG_BREAK() __builtin_debugtrap()
#elif defined(_MSC_VER)
#define WMCV_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__)
#define WMCV_DEBUG_BREAK() __builtin_debugtrap();
#endif

    static IAssertHandler* GAssertHandler;

    struct DefaultAssertHandler final : public IAssertHandler
    {
        void onHandleAssert(const source_location& loc, const char* expression, const char* msg ) const noexcept
        {
#ifdef MSVC
            OutputDebugStringA(expression);
#else
            printf("%s\n", expression);
#endif
            WMCV_DEBUG_BREAK();
        }
    };

    void HandleAssert(source_location loc, const char* expression, const char* msg ) noexcept
    {
        GAssertHandler->onHandleAssert(loc, expression, msg);
    }

    void SetAssertHandler(IAssertHandler* handler) noexcept
    {
        GAssertHandler = handler;
    }

    void CreateDefaultAssertHandler() noexcept
    {
        static DefaultAssertHandler s_defaultHandler;
        GAssertHandler = &s_defaultHandler;
    }

}
