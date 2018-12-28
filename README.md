#### 单元测试框架对比
单元测试是软件开发过程中最低级别的测试环节，一般由编码人员自己完成，其目的是隔离程序部件，并证明这些单个部件满足预期的功能。好的单元测试需要具备一下特点:
- 独立: 每个测试用例的测试结果不受其他测试的影响，保证每个测试用例前后程序状态一致。
- 有效的组织架构，清晰的命名: 各个测试用例针对不同的测试对象，而对单个测试对象而言，又可能有多个测试用例对应该对象的多个功能。好的习惯是把这些用例以层次结构的形式组织起来，并使用清晰的命名，使得我们通过阅读用例名称即可明了该用例的功能。
- 可移植、可复用: 平台无关。
- 当用例失败时，提供尽可能多的有效信息。

#### 1. Google Test && Google Mock
- 断言
    - ASSERT_* 系列的断言，当检查点失败时，退出当前函数（注意：并非退出当前案例）。 
    - EXPECT_* 系列的断言，当检查点失败时，继续往下执行。
    - 覆盖类型包括: 布尔型，数值型，浮点型，字符串型。还可以进行异常检查，谓词断言。可以自定义错误输出。
- 事件
    - 全局的，所有案例执行前后。
    - TestSuite级别的，在某一批案例中第一个案例前，最后一个案例执行后。
    - TestCase级别的，每个TestCase前后。
- 参数化测试
    - 可以将一组值依次传入到Case中进行测试，包括数值范围，数组，容器，迭代器，布尔值，以及由数组进行排列组合。
- 死亡测试
    - 对于不正确的输入，需要检查程序是否按照预期的方式挂掉。*_DEATH用于检查程序因给定错误崩溃。 *_EXIT用于检查程序因给定错误异常退出，检查退出码。
- 运行参数
    - 系统环境变量
    - 命令行参数
    - 代码中FLAG指定
    - 优先级：命令行参数 > 代码中指定FLAG > 系统环境变量。

支持死亡测试，与gmock搭配，但是它需要嵌入到项目中作为源代码进行编译，并且与Catch2和boost.test相比具有大量的宏，不方便记忆。

#### 2. Catch2
只要头文件，跨平台，不需要写main函数。
REQUIRE和CHECK宏几乎能够进行任何比较，便于使用。
比如浮点数比较, gtest的`EXPECT_FLOAT_EQ(0, a)` 可以使用 `CHECK (a == Approx (0).margin (some_eps))`
字符串比较，gtest的 `EXPECT_STREQ` 可以使用 `CHECK_THAT (str, Catch::Equals ("Expected str"))`
支持BDD测试用例:
```
SCENARIO("BDD test with zero", "[bdd]")
{
   WHEN("The number is 0") {
      THEN("The result is 0") {
         REQUIRE(fizzbuzz(0) == "0");
      }
   }
}
```
不再需要fixtures: 
```
TEST_CASE("DateTime", "[core]")
{
    const DateTime dt (1969, 7, 20, 20, 17, 40, 42, DateTimeReference::Utc);

    SECTION("GetYear")
    {
        CHECK (dt.GetYear () == 1969);
    }

    SECTION("GetMonth")
    {
        CHECK (dt.GetMonth () == 7);
    }
}
```
不足: 可以使用Fakeit进行mock,但是该框架相比gmock还是不够完整,死亡测试, 编译较久且生产的测试文件相对较大.

#### 3. boost.test && boost.turtle
支持DDT数据驱动测试,便于移植和修改，能够很好的处理异常和崩溃, 支持套件测试. 
不足: 不支持mock，但是可以搭配boost.turtle实现类似的工作,使用boost比较麻烦，略显臃肿。


所有3个框架都支持自动化测试,输出xml报告, 在cmake项目中可以一次性运行所有测试。如果需要一个完整的测试解决方案，可以选择gtest/gmock。 如果需要DDT数据驱动测试，可以使用boost.test + boost.turtle。 而Catch更轻巧，简洁好看，如果只想使用一堆单元测试，可以考虑它。 甚至可以将它与boost.turtle或者Fakeit集成在一起，但有点麻烦。

第一个链接是各个单元测试框架的支持特性汇总表。
#### Reference:
- https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks#C.2B.2B
- https://www.reddit.com/r/cpp/comments/4e9afx/most_popular_c_unit_testing_frameworks/
- http://gamesfromwithin.com/exploring-the-c-unit-testing-framework-jungle
- https://en.wikipedia.org/wiki/List_of_unit_testing_frameworks#C.2B.2B
- https://anteru.net/blog/2017/from-google-test-to-catch/index.html
- https://github.com/catchorg/Catch2
- https://www.cnblogs.com/fnlingnzb-learner/p/6927817.html
