//
// Created by edenzhong on 2018/8/30.
//
#include <gtest/gtest.h>
void Foo()
{
    int *pInt = 0;
    *pInt = 42 ;
}

TEST(FooDeathTest, Demo)
{
    EXPECT_DEATH(Foo(), "");
}

TEST(ExitDeathTest, Demo)
{
    EXPECT_EXIT(_exit(1),  testing::ExitedWithCode(1),  "");
}

TEST(MyDeathTest, TestOne) {
    testing::FLAGS_gtest_death_test_style = "threadsafe";
    // This test is run in the "threadsafe" style:
    ASSERT_DEATH(Foo(), "");
}

TEST(MyDeathTest, TestTwo) {
    // This test is run in the "fast" style:
    ASSERT_DEATH(Foo(), "");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(output) = "xml:";
    testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}