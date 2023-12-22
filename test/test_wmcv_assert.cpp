#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define WMCV_ENABLE_ASSERTS
#include "wmcv_assert/wmcv_assert.h"

class MockAssertHandler : public wmcv::IAssertHandler
{
public:
    MOCK_METHOD(void, onHandleAssert, (const wmcv::source_location&, const std::string_view, const std::string_view), (const, noexcept, override));
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

TEST_F(AssertFixture, test_assert_msg_calls_onHandleAssert_on_false_expression)
{
    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtLeast(1));
    
    WMCV_ASSERT(false);
}

TEST_F(AssertFixture, test_assert_msg_calls_onHandleAssert_on_true_expression)
{
    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtMost(0));
    
    WMCV_ASSERT_MSG(true, "Custom Assert Message");
}

TEST_F(AssertFixture, test_fatal_calls_onHandleAssert)
{
    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtLeast(1));
    
    WMCV_FATAL();
}

TEST_F(AssertFixture, test_fatal_msg_calls_onHandleAssert)
{
    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtLeast(1));
    
    WMCV_FATAL_MSG("Fatal Error From a Unit Test");
}

TEST_F(AssertFixture, test_assert_msg_prints_custom_message_on_false_expression)
{
    const std::string expected = "Custom Assert Message 1234";
    std::string result;
    
    ON_CALL(mockHandler, onHandleAssert)
        .WillByDefault([&result](const wmcv::source_location&, const std::string_view, const std::string_view message){ result = message; });
    
    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtLeast(1));
    
    WMCV_ASSERT_MSG(false, "Custom Assert Message %d", 1234);
    EXPECT_EQ(expected, result);
}

TEST_F(AssertFixture, test_assert_msg_does_not_print_custom_message_on_true_expression)
{
    const std::string_view expected = "";
    std::string_view result;
    
    ON_CALL(mockHandler, onHandleAssert)
        .WillByDefault([&result](const wmcv::source_location&, const std::string_view, const std::string_view message){ result = message; });
    
    EXPECT_CALL(mockHandler, onHandleAssert)
        .Times(::testing::AtMost(0));
    
    WMCV_ASSERT_MSG(true, "Custom Assert Message");
    EXPECT_EQ(expected, result);
}
