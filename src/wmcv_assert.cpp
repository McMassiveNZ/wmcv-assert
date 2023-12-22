#include "pch.h"
#include "wmcv_assert/wmcv_assert.h"

namespace wmcv
{

#ifdef WMCV_ASSERTS_ENABLED

#if defined(__GNUC__) || defined(__clang__)
#define WMCV_DEBUG_BREAK() __builtin_trap()
#elif defined(_MSC_VER)
#define WMCV_DEBUG_BREAK() __debugbreak()
#endif

    static IAssertHandler* GAssertHandler;

    static const char* GetAssertMessage(std::string_view customMessage)
    {
        if( customMessage.empty())
        {
            return R""""(Assertion Expression: %s FAILED
    In File: %s
    On Line: %llu)"""";
        }
        
        return R""""(Assertion Expression: %s FAILED
    %s
    In File: %s
    On Line: %llu)"""";
    }

    struct DefaultAssertHandler final : public IAssertHandler
    {
        void onHandleAssert(const source_location& loc, std::string_view expression, std::string_view message) const noexcept
        {
            const char* fmt = GetAssertMessage(message);
#ifdef _MSC_VER
            OutputDebugStringA(buffer.data());
#else
			printf(fmt, expression, loc.file_name(), loc.line());
#endif
            WMCV_DEBUG_BREAK();
        }
    };

    void HandleAssert(source_location loc, const char* expression, const char* fmt, ... ) noexcept
    {
        std::array<char, 512> buffer = {};
        
        va_list args;
        va_start(args, fmt);
        const auto num_chars = vsnprintf(buffer.data(), buffer.size(), fmt, args);
        va_end(args);
        
        auto message = (num_chars >= 0 ) ? std::string_view(buffer.data(), num_chars) : std::string_view{};
        GAssertHandler->onHandleAssert(loc, expression, message);
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
#else
void HandleAssert(source_location, const char*, const char*, ...) noexcept
{
}

void SetAssertHandler(IAssertHandler*) noexcept
{
}

void CreateDefaultAssertHandler() noexcept
{
}
#endif
}
