#include "leetcode/problems/number-of-digit-one.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_233 {

class NumberOfDigitOneTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfDigitOneSolution solution;
};

TEST_P(NumberOfDigitOneTest, Example1) {
  // n = 13: 1, 10, 11, 12, 13 中的 1
  // 1(1个), 10(1个), 11(2个), 12(1个), 13(1个) = 6
  int n = 13;
  int expected = 6;
  EXPECT_EQ(expected, solution.countDigitOne(n));
}

TEST_P(NumberOfDigitOneTest, Example2) {
  int n = 0;
  int expected = 0;
  EXPECT_EQ(expected, solution.countDigitOne(n));
}

TEST_P(NumberOfDigitOneTest, EdgeCaseSingleDigit) {
  // 测试个位数
  EXPECT_EQ(0, solution.countDigitOne(0));  // 0 中没有 1
  EXPECT_EQ(1, solution.countDigitOne(1));  // 1 中有 1 个 1
  EXPECT_EQ(1, solution.countDigitOne(5));  // 只有数字 1 有 1 个 1
  EXPECT_EQ(1, solution.countDigitOne(9));  // 只有数字 1 有 1 个 1
}

TEST_P(NumberOfDigitOneTest, EdgeCaseSmallNumbers) {
  // 测试小数值
  EXPECT_EQ(2, solution.countDigitOne(10));  // 1(1个), 10(1个) = 2
  EXPECT_EQ(4, solution.countDigitOne(11));  // 1, 10, 11(2个) = 4
  EXPECT_EQ(5, solution.countDigitOne(12));  // 1, 10, 11(2个), 12 = 5
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfDigitOneTest,
    ::testing::ValuesIn(NumberOfDigitOneSolution().getStrategyNames()));

}  // namespace problem_233
}  // namespace leetcode
