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
    virtual void onHandleAssert(const source_location& location, const std::string_view expression, const std::string_view message) const noexcept = 0;
};

void HandleAssert(source_location location, const char* expression, const char* fmt, ...) noexcept;
void SetAssertHandler(IAssertHandler* handler) noexcept;
void CreateDefaultAssertHandler() noexcept;

}

#ifdef WMCV_ASSERTS_ENABLED

#define WMCV_ASSERT(x)\
do{ if(!(x)){ wmcv::HandleAssert(wmcv::source_location::current(), #x, "");}} while(false)

#define WMCV_ASSERT_MSG(x, ...) \
do{ if(!(x)){ wmcv::HandleAssert(wmcv::source_location::current(), #x, __VA_ARGS__ );}} while(false)

#define WMCV_FATAL() WMCV_ASSERT(false)
#define WMCV_FATAL_MSG(...) WMCV_ASSERT_MSG(false, __VA_ARGS__)

#else

#define WMCV_ASSERT(x) do { ((void)(x)); }while(false)
#define WMCV_ASSERT_MSG(x, ...) do { ((void)(x)); }while(false)
#define WMCV_FATAL() do {} while(false)
#define WMCV_FATAL_MSG(...) do { ((void)(__VA_ARGS__)); }while(false)

#endif //WMCV_ASSERTS_ENABLED
#endif //WMCV_ASSERT_H_INCLUDED
