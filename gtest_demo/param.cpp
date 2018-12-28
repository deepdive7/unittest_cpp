//
// Created by edenzhong on 2018/8/30.
//

#include <gtest/gtest.h>

class IsGTZeroTest : public::testing::TestWithParam<int> {};

TEST_P(IsGTZeroTest, HandleTrueReturn)
{
    int n =  GetParam();
    EXPECT_TRUE(n > 0);
}

INSTANTIATE_TEST_CASE_P(TrueReturn1, IsGTZeroTest, testing::Values(3, 5, 11, 23, 17));
INSTANTIATE_TEST_CASE_P(TrueReturn2, IsGTZeroTest, testing::Range(1,3));
// 还可以使用容器ValuesIn(container) and ValuesIn(begin, end), Combine(g1, g2, ..., gN) 排列组合

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}