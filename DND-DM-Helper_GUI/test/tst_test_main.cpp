
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

TEST(test_main, test_main)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
