#include "leetcode/problems/minimum-deletions-to-make-string-balanced.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1653 {

class MinimumDeletionsToMakeStringBalancedTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumDeletionsToMakeStringBalancedSolution solution;
};

TEST_P(MinimumDeletionsToMakeStringBalancedTest, Example1) {
  string s = "aababbab";
  int expected = 2;
  EXPECT_EQ(expected, solution.minimumDeletions(s));
}

TEST_P(MinimumDeletionsToMakeStringBalancedTest, Example2) {
  string s = "bbaaaaabb";
  int expected = 2;
  EXPECT_EQ(expected, solution.minimumDeletions(s));
}

// 边界：单个字符
TEST_P(MinimumDeletionsToMakeStringBalancedTest, SingleChar) {
  EXPECT_EQ(0, solution.minimumDeletions("a"));
  EXPECT_EQ(0, solution.minimumDeletions("b"));
}

// 边界：已经平衡的字符串（全a、全b、或a在前b在后）
TEST_P(MinimumDeletionsToMakeStringBalancedTest, AlreadyBalanced) {
  EXPECT_EQ(0, solution.minimumDeletions("aaaa"));
  EXPECT_EQ(0, solution.minimumDeletions("bbbb"));
  EXPECT_EQ(0, solution.minimumDeletions("aaabbb"));
  EXPECT_EQ(0, solution.minimumDeletions("aabbb"));
}

// 边界：完全不平衡（所有b在前，所有a在后）
TEST_P(MinimumDeletionsToMakeStringBalancedTest, CompletelyUnbalanced) {
  // "bbbaaa" 需要删除 3 个 'b' 或 3 个 'a'，最小是 3
  EXPECT_EQ(3, solution.minimumDeletions("bbbaaa"));
  EXPECT_EQ(2, solution.minimumDeletions("bbaa"));
}

// 边界：交替字符串
TEST_P(MinimumDeletionsToMakeStringBalancedTest, Alternating) {
  // "abab": 删除 index 1 的'b' -> "aab"（平衡），或删除 index 2 的'a' -> "abb"（平衡）
  // 最优只需删除 1 个
  EXPECT_EQ(1, solution.minimumDeletions("abab"));
  // "baba": 需要删除 2 个才能平衡（如变成 "bb"、"aa" 或 "ab"）
  EXPECT_EQ(2, solution.minimumDeletions("baba"));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumDeletionsToMakeStringBalancedTest,
    ::testing::ValuesIn(MinimumDeletionsToMakeStringBalancedSolution().getStrategyNames()));

}  // namespace problem_1653
}  // namespace leetcode
