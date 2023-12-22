#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wmcv_assert/wmcv_assert.h"

class MockAssertHandler : public wmcv::IAssertHandler
{
public:
    MOCK_METHOD(void, onHandleAssert, (const wmcv::source_location&, const char*, const char*), (const, noexcept, override));
};

TEST(test_wmcv_assert, test_assert_calls_onHandleAssert)
{
    MockAssertHandler mockHandler;
    wmcv::SetAssertHandler(&mockHandler);

    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtLeast(1));
    
    WMCV_ASSERT(7*6 != 42);
}
