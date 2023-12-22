#ifndef WMCV_ASSERT_H_INCLUDED
#define WMCV_ASSERT_H_INCLUDED

namespace wmcv
{
#if __cpp_lib_source_location
    using source_location = std::source_location;
#else
struct SourceLocation
{
    [[nodiscard]] static consteval auto current(const char* file = __FILE__, size_t line = __LINE__ ) noexcept -> SourceLocation
    {
        return { .m_file = file, .m_line = line };
    }

    [[nodiscard]] auto file_name() const noexcept -> const char* { return m_file; }
	[[nodiscard]] auto line() const noexcept -> size_t { return m_line; }

    const char* m_file;
    size_t m_line;
};
using source_location = SourceLocation;
#endif

struct IAssertHandler
{
    virtual ~IAssertHandler() = default;
    virtual void onHandleAssert(const source_location& location, const char* expression, const char* msg) const noexcept = 0;
};

void HandleAssert(source_location location, const char* expression, const char* message) noexcept;
void SetAssertHandler(IAssertHandler* handler) noexcept;
void CreateDefaultAssertHandler() noexcept;
}

#define WMCV_ASSERT(x) \
do\
{\
    if (!(x)) \
    { \
        wmcv::HandleAssert(wmcv::source_location::current(), #x, "Assert Failed");\
    }\
} \
while (false)
#endif //WMCV_ASSERT_H_INCLUDED
