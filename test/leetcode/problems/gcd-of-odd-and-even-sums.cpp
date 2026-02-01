
#include "leetcode/problems/gcd-of-odd-and-even-sums.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3658 {

class GcdOfOddAndEvenSumsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  GcdOfOddAndEvenSumsSolution solution;
};

TEST_P(GcdOfOddAndEvenSumsTest, Example1) {
  int n = 4;
  int expected = 4;
  EXPECT_EQ(expected, solution.gcdOfOddEvenSums(n));
}

TEST_P(GcdOfOddAndEvenSumsTest, Example2) {
  int n = 5;
  int expected = 5;
  EXPECT_EQ(expected, solution.gcdOfOddEvenSums(n));
}

TEST_P(GcdOfOddAndEvenSumsTest, SingleElement) {
  int n = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.gcdOfOddEvenSums(n));
}

TEST_P(GcdOfOddAndEvenSumsTest, LargeN) {
  int n = 1000;
  int expected = 1000;
  EXPECT_EQ(expected, solution.gcdOfOddEvenSums(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, GcdOfOddAndEvenSumsTest,
    ::testing::ValuesIn(GcdOfOddAndEvenSumsSolution().getStrategyNames()));

}  // namespace problem_3658
}  // namespace leetcode
