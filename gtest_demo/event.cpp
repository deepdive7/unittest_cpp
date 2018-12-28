//
// Created by edenzhong on 2018/8/30.
//

#include <gtest/gtest.h>

class FooEnvironment : public testing::Environment {
public:
    virtual void SetUp() {
        std::cout << "Foo FooEnvironment SetUP" << std::endl;
    }

    virtual void TearDown() {
        std::cout << "Foo FooEnvironment TearDown" << std::endl;
    }
};

class FooTest : public testing::Test {
protected:
    static std::string shared_resource_;

    static void SetUpTestCase() {
        shared_resource_ = "Hello C++";
    };

    static void TearDownTestCase() {
        std::cout << "Reset shared_resource\n";
    };
};

//TEST_F(FooTest, Test1) {
//    std::cout << "Get shared resource:" << shared_resource_ << " in Test1\n";
//}
//
//TEST_F(FooTest, Test2) {
//    std::cout << "Get shared resource:" << shared_resource_ << " in Test2\n";
//}

class FooCalc {
public:
    void Init() {
        std::cout << "Start Calc\n";
    };

    void Finalize() {
        std::cout << "Finish Calc\n";
    };

    int Calc(int a, int b) {
        return a * b;
    };
};

class FooCalcTest : public testing::Test {
protected:
    virtual void SetUp() {
        m_foo.Init();
    }

    virtual void TearDown() {
        m_foo.Finalize();
    }

    FooCalc m_foo;
};

TEST_F(FooCalcTest, Test1) {
    EXPECT_EQ(4, m_foo.Calc(2, 2));
}

TEST_F(FooCalcTest, Test2) {
    EXPECT_EQ(5, m_foo.Calc(2, 2));
}

int main(int argc, char *argv[]) {
    testing::AddGlobalTestEnvironment(new FooEnvironment);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}