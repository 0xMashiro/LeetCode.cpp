#include "leetcode/problems/consecutive-numbers-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_829 {

class ConsecutiveNumbersSumTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConsecutiveNumbersSumSolution solution;
};

TEST_P(ConsecutiveNumbersSumTest, Example1) {
  int n = 5;
  int expected = 2;
  EXPECT_EQ(expected, solution.consecutiveNumbersSum(n));
}

TEST_P(ConsecutiveNumbersSumTest, Example2) {
  int n = 9;
  int expected = 3;
  EXPECT_EQ(expected, solution.consecutiveNumbersSum(n));
}

TEST_P(ConsecutiveNumbersSumTest, Example3) {
  int n = 15;
  int expected = 4;
  EXPECT_EQ(expected, solution.consecutiveNumbersSum(n));
}

TEST_P(ConsecutiveNumbersSumTest, SingleElement) {
  // n = 1，只有 1 本身
  int n = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.consecutiveNumbersSum(n));
}

TEST_P(ConsecutiveNumbersSumTest, PrimeNumber) {
  // n = 3，3 = 1+2 或 3 本身
  int n = 3;
  int expected = 2;
  EXPECT_EQ(expected, solution.consecutiveNumbersSum(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConsecutiveNumbersSumTest,
    ::testing::ValuesIn(ConsecutiveNumbersSumSolution().getStrategyNames()));

}  // namespace problem_829
}  // namespace leetcode
