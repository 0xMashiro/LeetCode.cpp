#include "leetcode/problems/concatenate-non-zero-digits-and-multiply-by-sum-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3754 {

class ConcatenateNonZeroDigitsAndMultiplyBySumITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConcatenateNonZeroDigitsAndMultiplyBySumISolution solution;
};

TEST_P(ConcatenateNonZeroDigitsAndMultiplyBySumITest, Example1) {
  int n = 10203004;
  long long expected = 12340;
  EXPECT_EQ(expected, solution.sumAndMultiply(n));
}

TEST_P(ConcatenateNonZeroDigitsAndMultiplyBySumITest, Example2) {
  int n = 1000;
  long long expected = 1;
  EXPECT_EQ(expected, solution.sumAndMultiply(n));
}

TEST_P(ConcatenateNonZeroDigitsAndMultiplyBySumITest, SelfAuthoredAllZeros) {
  int n = 0;
  long long expected = 0;
  EXPECT_EQ(expected, solution.sumAndMultiply(n));
}

TEST_P(ConcatenateNonZeroDigitsAndMultiplyBySumITest, SelfAuthoredAllNonZero) {
  int n = 123;
  // x = 123, sum = 6, result = 738
  long long expected = 738;
  EXPECT_EQ(expected, solution.sumAndMultiply(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConcatenateNonZeroDigitsAndMultiplyBySumITest,
    ::testing::ValuesIn(ConcatenateNonZeroDigitsAndMultiplyBySumISolution().getStrategyNames()));

}  // namespace problem_3754
}  // namespace leetcode
