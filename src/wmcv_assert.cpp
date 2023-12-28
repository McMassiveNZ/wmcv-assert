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

    static const char* GetAssertFormatMessage(const std::string_view message)
	{
		if (!message.empty())
		{
			return R""""(Assertion Expression: %s FAILED
    %hs
    In File: %hs
    On Line: %llu)"""";
		}
        
		return R""""(Assertion Expression: %s FAILED
    In File: %hs
    On Line: %u)"""";
    }

    static void DebugPrintAssertMessage(const char* fmt, const wmcv::source_location& loc, const std::string_view expression, const std::string_view message) noexcept
    {
#ifdef _MSC_VER
		std::array<char, 2048> buffer = {};

		char* msg = buffer.data();
		const size_t size = buffer.size();
		const char* expr = expression.data();

		if (message.empty())
		{
			snprintf(msg, size, fmt, expr, loc.file_name(), loc.line());
		}
		else
		{
			snprintf(msg, size, fmt, expr, message.data(), loc.file_name(), loc.line());
		}

		OutputDebugStringA(msg);
#else
        if (message.empty())
        {
			printf(fmt, expression.data(), loc.file_name(), loc.line());
        }
		else
		{
			printf(fmt, expression.data(), message.data(), loc.file_name(), loc.line());
		}
#endif
    }

    struct DefaultAssertHandler final : public IAssertHandler
    {
        void onHandleAssert(const source_location& loc, const std::string_view expression, const std::string_view message) const noexcept
        {
			const char* fmt = GetAssertFormatMessage(message);
			DebugPrintAssertMessage(fmt, loc, expression, message);
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
        GAssertHandler->onHandleAssert(loc, expression, message.data());
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
