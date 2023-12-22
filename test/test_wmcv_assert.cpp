#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wmcv_assert/wmcv_assert.h"

class MockAssertHandler : public wmcv::IAssertHandler
{
public:
    MOCK_METHOD(void, onHandleAssert, (const wmcv::source_location&, const char*, const char*), (const, noexcept, override));
};

class AssertFixture : public ::testing::Test
{
public:
    void SetUp()
    {
		wmcv::SetAssertHandler(&mockHandler);
    }

    void TearDown() 
    {
		wmcv::CreateDefaultAssertHandler();
    }

    MockAssertHandler mockHandler;
};

TEST_F(AssertFixture, test_assert_calls_onHandleAssert_on_false_expression)
{
    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtLeast(1));
    
    WMCV_ASSERT(false);
}

TEST_F(AssertFixture, test_assert_calls_onHandleAssert_on_true_expression)
{
    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtMost(0));
    
    WMCV_ASSERT(true);
}