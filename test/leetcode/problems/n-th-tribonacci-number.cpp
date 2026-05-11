#include "leetcode/problems/n-th-tribonacci-number.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1137 {

class NThTribonacciNumberTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NThTribonacciNumberSolution solution;
};

TEST_P(NThTribonacciNumberTest, Example1) {
  int n = 4;
  int expected = 4;
  EXPECT_EQ(expected, solution.tribonacci(n));
}

TEST_P(NThTribonacciNumberTest, Example2) {
  int n = 25;
  int expected = 1389537;
  EXPECT_EQ(expected, solution.tribonacci(n));
}

TEST_P(NThTribonacciNumberTest, SelfAuthoredBaseCase) {
  EXPECT_EQ(0, solution.tribonacci(0));
  EXPECT_EQ(1, solution.tribonacci(1));
  EXPECT_EQ(1, solution.tribonacci(2));
}

TEST_P(NThTribonacciNumberTest, SelfAuthoredSmallValues) {
  // T_3 = 0+1+1 = 2
  EXPECT_EQ(2, solution.tribonacci(3));
  // T_4 = 1+1+2 = 4
  EXPECT_EQ(4, solution.tribonacci(4));
  // T_5 = 1+2+4 = 7
  EXPECT_EQ(7, solution.tribonacci(5));
  // T_6 = 2+4+7 = 13
  EXPECT_EQ(13, solution.tribonacci(6));
  // T_7 = 4+7+13 = 24
  EXPECT_EQ(24, solution.tribonacci(7));
}

TEST_P(NThTribonacciNumberTest, SelfAuthoredMaxConstraint) {
  // n = 37, 检查 32-bit 范围内
  int result = solution.tribonacci(37);
  EXPECT_GE(result, 0);
  EXPECT_LE(result, INT_MAX);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NThTribonacciNumberTest,
    ::testing::ValuesIn(NThTribonacciNumberSolution().getStrategyNames()));

}  // namespace problem_1137
}  // namespace leetcode
