#include "leetcode/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3007 {

class MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKSolution solution;
};

TEST_P(MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKTest, Example1) {
  long long k = 9;
  int x = 1;
  long long expected = 6;
  EXPECT_EQ(expected, solution.findMaximumNumber(k, x));
}

TEST_P(MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKTest, Example2) {
  long long k = 7;
  int x = 2;
  long long expected = 9;
  EXPECT_EQ(expected, solution.findMaximumNumber(k, x));
}

  // 输入: k = 521, x = 8
  // 期望: 1160
TEST_P(MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKTest, WrongAnswerCase1) {
  long long k = 521;
  int x = 8;
  long long expected = 1160;
  EXPECT_EQ(expected, solution.findMaximumNumber(k, x));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, 
    MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKTest,
    ::testing::ValuesIn(MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKSolution().getStrategyNames()));

}  // namespace problem_3007
}  // namespace leetcode
