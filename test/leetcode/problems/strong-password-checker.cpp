#include "leetcode/problems/strong-password-checker.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_420 {

class StrongPasswordCheckerTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  StrongPasswordCheckerSolution solution;
};

// 示例1：单字符，需要5步（插入5个）
TEST_P(StrongPasswordCheckerTest, Example1) {
  EXPECT_EQ(solution.strongPasswordChecker("a"), 5);
}

// 示例2：3字符，有大写有小写有数字
// 长度=3，需要插入3个达到长度6
TEST_P(StrongPasswordCheckerTest, Example2) {
  EXPECT_EQ(solution.strongPasswordChecker("aA1"), 3);
}

// 示例3：已经是强密码
TEST_P(StrongPasswordCheckerTest, Example3) {
  EXPECT_EQ(solution.strongPasswordChecker("1337C0d3"), 0);
}

// 边界测试：空字符串（题目约束>=1，但测试边界）
TEST_P(StrongPasswordCheckerTest, EmptyString) {
  // 需要6个字符，且包含三种类型
  EXPECT_EQ(solution.strongPasswordChecker(""), 6);
}

// 边界测试：恰好6个字符，但只有一种类型且有连续重复
TEST_P(StrongPasswordCheckerTest, Length6OneType) {
  // "aaaaaa" - 缺2种类型，有2个连续(6/3=2)
  // max(2, 2) = 2
  EXPECT_EQ(solution.strongPasswordChecker("aaaaaa"), 2);
}

// 边界测试：长度大于20，需要删除
TEST_P(StrongPasswordCheckerTest, LongPassword) {
  // "aaaaaaaaaaaaaaaaaaaaa" (21个a)
  // 需要删除1个，且需要替换（21/3=7次替换）
  // 删除1个在%3==0的序列上（21%3=0），可以省1次替换
  // 最终：1 + max(6, 3) = 1 + 6 = 7
  EXPECT_EQ(solution.strongPasswordChecker("aaaaaaaaaaaaaaaaaaaaa"), 7);
}

// 测试：长度20但有连续重复
TEST_P(StrongPasswordCheckerTest, Length20WithRepeat) {
  // "aaaaA1aaaaaaaaaaaaaa" - 20个字符：4a + A + 1 + 14a
  // 连续a序列：前4个a，后14个a
  // 4个a需要1次替换，14个a需要4次替换，共5次
  // 不缺类型，所以答案是5
  EXPECT_EQ(solution.strongPasswordChecker("aaaaA1aaaaaaaaaaaaaa"), 5);
}

// 测试：超过20个字符且有连续重复
TEST_P(StrongPasswordCheckerTest, Over20WithRepeat) {
  // "aaaaaaaaaaaaaaaaaaaaaa" (22个a)
  // 需要删除2个，有22/3=7次替换需求
  // 删除策略：优先删除%3==0的
  // 22%3=1，不是%3==0
  // 删除2个（从长度22变成20）
  // 可以节省 0 次替换（删2个对%3==1的序列不能省）
  // 删除后20个a，需要6次替换，缺2种类型
  // 答案 = 2 + max(6, 2) = 8
  EXPECT_EQ(solution.strongPasswordChecker("aaaaaaaaaaaaaaaaaaaaaa"), 8);
}

// 测试：三种类型都缺
TEST_P(StrongPasswordCheckerTest, MissingAllTypes) {
  // "!!!!!!!!" - 8个特殊字符，缺3种类型
  // 8/3 = 2次替换来打破连续
  // 2次替换可以提供2种类型，还需要1种类型
  // 总共3次
  EXPECT_EQ(solution.strongPasswordChecker("!!!!!!!!"), 3);
}

// 测试：长度小于6且有连续重复
TEST_P(StrongPasswordCheckerTest, ShortWithRepeat) {
  // "aaa" - 长度3，缺2种类型
  // 需要插入3个达到长度6
  // 答案是 max(3, 2) = 3
  EXPECT_EQ(solution.strongPasswordChecker("aaa"), 3);
}

// 测试：长度19（17a + A + 1）
TEST_P(StrongPasswordCheckerTest, Length19) {
  // "aaaaaaaaaaaaaaaaaA1" (17个a + A + 1 = 19个字符)
  // 不缺类型
  // 17个连续a需要 17/3 = 5 次替换
  EXPECT_EQ(solution.strongPasswordChecker("aaaaaaaaaaaaaaaaaA1"), 5);
}

// 测试：长度21（19a + A + 1），需要删除
TEST_P(StrongPasswordCheckerTest, Length21) {
  // "aaaaaaaaaaaaaaaaaaaA1" (19个a + A + 1 = 21个字符)
  // 需要删除1个
  // 19个a是连续，19%3=1，删1个不能省替换
  // 删除1个后19个a，需要 19/3 = 6 次替换
  // 不缺类型
  // 答案 = 1 + 6 = 7
  EXPECT_EQ(solution.strongPasswordChecker("aaaaaaaaaaaaaaaaaaaA1"), 7);
}

// 测试：复杂情况，多个连续序列
TEST_P(StrongPasswordCheckerTest, MultipleSequences) {
  // "aaaBBBcccDDDeeeFFF1"
  // 长度19，有6个序列各3个字符
  // 每个序列需要1次替换，共6次
  // 检查类型：有小写、大写、数字，不缺
  EXPECT_EQ(solution.strongPasswordChecker("aaaBBBcccDDDeeeFFF1"), 6);
}

// 额外测试：长度刚好20，全部同字符
TEST_P(StrongPasswordCheckerTest, Length20AllSame) {
  // "aaaaaaaaaaaaaaaaaaaa" (20个a)
  // 不缺小写，缺大写和数字
  // 20/3 = 6 次替换
  // 答案 = max(6, 2) = 6
  EXPECT_EQ(solution.strongPasswordChecker("aaaaaaaaaaaaaaaaaaaa"), 6);
}

// 额外测试：长度23，需要删除3个
// 测试：连续5个相同字符
TEST_P(StrongPasswordCheckerTest, FiveInARow) {
  // "aaaaaA1" - 7字符，5个a连续
  // 5/3 = 1 次替换
  // 不缺类型
  EXPECT_EQ(solution.strongPasswordChecker("aaaaaA1"), 1);
}

// 测试：ABABAB模式，无连续重复
TEST_P(StrongPasswordCheckerTest, NoRepeat) {
  // "aBaBaB123" - 无连续重复，但检查类型
  // 有小写、大写、数字
  EXPECT_EQ(solution.strongPasswordChecker("aBaBaB123"), 0);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, StrongPasswordCheckerTest,
    ::testing::ValuesIn(StrongPasswordCheckerSolution().getStrategyNames()));

}  // namespace problem_420
}  // namespace leetcode
