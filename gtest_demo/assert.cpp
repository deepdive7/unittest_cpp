//
// Created by edenzhong on 2018/8/29.
//

#include <gtest/gtest.h>

TEST(ASSERT_DEMO, NumCmp){
    int a {3};
    EXPECT_EQ(3, a);
    EXPECT_NE(3, a-1);
    EXPECT_GE(3, a);
    EXPECT_GT(3, a-1);
    EXPECT_LE(3, a);
    EXPECT_LT(3, a+1);
}

TEST(ASSERT_DEMO, BoolCmp){
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);
}

TEST(ASSERT_DEMO, StrCmp){
    std::string strCoderZh = "CoderZh";
    std::wstring wstrCoderZh = L"CoderZh";

    const char* pszCoderZh = strCoderZh.c_str();
    const wchar_t* wszCoderZh = wstrCoderZh.c_str();


    EXPECT_STREQ("CoderZh", pszCoderZh);
    EXPECT_STREQ(L"CoderZh", wszCoderZh);

    EXPECT_STRNE("CnBlogs", pszCoderZh);
    EXPECT_STRNE(L"CnBlogs", wszCoderZh);

    EXPECT_STRCASEEQ("coderzh", pszCoderZh);
    //EXPECT_STRCASEEQ(L"coderzh", wszCoderZh);    不支持wchar_t
}

TEST(ASSERT_DEMO, ExplicitRes){
    // ADD_FAILURE() << "Sorry";
    SUCCEED();
}

int Foo(int a, int b)
{
    if (a == 0 || b == 0)
    {
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return b;
    return Foo(b, c);
}

TEST(ASSERT_DEMO, Throw)
{
    EXPECT_ANY_THROW(Foo(10, 0));
    EXPECT_THROW(Foo(0, 5), char*);
}


bool MutuallyPrime(int m, int n)
{
    return Foo(m , n) > 1;
}

TEST(ASSERT_DEMO, PredicateAssertion)
{
    int m = 6, n = 7;
    // 2代表参数个数
    EXPECT_PRED2(MutuallyPrime, m, n);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
