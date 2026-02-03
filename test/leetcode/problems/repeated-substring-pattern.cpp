#include "leetcode/problems/repeated-substring-pattern.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_459 {

class RepeatedSubstringPatternTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RepeatedSubstringPatternSolution solution;
};

TEST_P(RepeatedSubstringPatternTest, Example1) {
  string s = "abab";
  bool expected = true;
  EXPECT_EQ(expected, solution.repeatedSubstringPattern(s));
}

TEST_P(RepeatedSubstringPatternTest, Example2) {
  string s = "aba";
  bool expected = false;
  EXPECT_EQ(expected, solution.repeatedSubstringPattern(s));
}

TEST_P(RepeatedSubstringPatternTest, Example3) {
  string s = "abcabcabcabc";
  bool expected = true;
  EXPECT_EQ(expected, solution.repeatedSubstringPattern(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RepeatedSubstringPatternTest,
    ::testing::ValuesIn(RepeatedSubstringPatternSolution().getStrategyNames()));

}  // namespace problem_459
}  // namespace leetcode
