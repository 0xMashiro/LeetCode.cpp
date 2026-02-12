#include "leetcode/problems/longest-balanced-substring-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3713 {

class LongestBalancedSubstringITest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestBalancedSubstringISolution solution;
};

TEST_P(LongestBalancedSubstringITest, Example1) {
  string s = "abbac";
  int expected = 4;
  EXPECT_EQ(expected, solution.longestBalanced(s));
}

TEST_P(LongestBalancedSubstringITest, Example2) {
  string s = "zzabccy";
  int expected = 4;
  EXPECT_EQ(expected, solution.longestBalanced(s));
}

TEST_P(LongestBalancedSubstringITest, Example3) {
  string s = "aba";
  int expected = 2;
  EXPECT_EQ(expected, solution.longestBalanced(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestBalancedSubstringITest,
    ::testing::ValuesIn(LongestBalancedSubstringISolution().getStrategyNames()));

}  // namespace problem_3713
}  // namespace leetcode
