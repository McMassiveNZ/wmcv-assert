#ifndef WMCV_ASSERT_H_INCLUDED
#define WMCV_ASSERT_H_INCLUDED

namespace wmcv
{
#ifdef __cpp_lib_source_location
    using source_location = std::source_location
#else

struct SourceLocation
{
    const char* file_name;
    size_t line;
    
    [[nodiscard]] static consteval auto current(const char* file = __FILE__, size_t line = __LINE__ ) noexcept -> SourceLocation
    {
        return SourceLocation{ .file_name = file, .line = line };
    }
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
        HandleAssert(wmcv::source_location::current(), #x, "Assert Failed");\
    }\
} \
while (false)
#endif //WMCV_ASSERT_H_INCLUDED
