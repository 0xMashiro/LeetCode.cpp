
#include "leetcode/problems/guess-number-higher-or-lower.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_374 {

// Mock guess API 的全局变量
static int g_pick;

// Mock guess API 实现
int guess(int num) {
  if (num > g_pick) return -1;
  if (num < g_pick) return 1;
  return 0;
}

class GuessNumberHigherOrLowerTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  GuessNumberHigherOrLowerSolution solution;
};

TEST_P(GuessNumberHigherOrLowerTest, Example1) {
  // Input: n = 10, pick = 6
  // Output: 6
  g_pick = 6;
  int n = 10;
  EXPECT_EQ(6, solution.guessNumber(n));
}

TEST_P(GuessNumberHigherOrLowerTest, Example2) {
  // Input: n = 1, pick = 1
  // Output: 1
  g_pick = 1;
  int n = 1;
  EXPECT_EQ(1, solution.guessNumber(n));
}

TEST_P(GuessNumberHigherOrLowerTest, Example3) {
  // Input: n = 2, pick = 1
  // Output: 1
  g_pick = 1;
  int n = 2;
  EXPECT_EQ(1, solution.guessNumber(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, GuessNumberHigherOrLowerTest,
    ::testing::ValuesIn(GuessNumberHigherOrLowerSolution().getStrategyNames()));

}  // namespace problem_374
}  // namespace leetcode
