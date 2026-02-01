
#include "leetcode/problems/palindrome-partitioning-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_132 {

class PalindromePartitioningIiTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PalindromePartitioningIiSolution solution;
};

TEST_P(PalindromePartitioningIiTest, Example1) {
  string s = "aab";
  int expected = 1;
  EXPECT_EQ(expected, solution.minCut(s));
}

TEST_P(PalindromePartitioningIiTest, Example2) {
  string s = "a";
  int expected = 0;
  EXPECT_EQ(expected, solution.minCut(s));
}

TEST_P(PalindromePartitioningIiTest, Example3) {
  string s = "ab";
  int expected = 1;
  EXPECT_EQ(expected, solution.minCut(s));
}

TEST_P(PalindromePartitioningIiTest, AllSameCharacters) {
  // 全是相同字符，本身就是一个回文，不需要切割
  string s = "aaaaa";
  int expected = 0;
  EXPECT_EQ(expected, solution.minCut(s));
}

TEST_P(PalindromePartitioningIiTest, AllDifferentCharacters) {
  // 全不同字符，每个字符都要切
  string s = "abcde";
  int expected = 4;
  EXPECT_EQ(expected, solution.minCut(s));
}

TEST_P(PalindromePartitioningIiTest, PalindromeString) {
  // 本身就是回文的字符串
  string s = "abba";
  int expected = 0;
  EXPECT_EQ(expected, solution.minCut(s));
}

TEST_P(PalindromePartitioningIiTest, LongPalindromePrefix) {
  // 长回文前缀的情况
  string s = "abacded";
  int expected = 2;  // ["aba", "c", "ded"] 或 ["a", "bacab"]? 不对，是 aba + c + ded = 2 刀
  EXPECT_EQ(expected, solution.minCut(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PalindromePartitioningIiTest,
    ::testing::ValuesIn(PalindromePartitioningIiSolution().getStrategyNames()));

}  // namespace problem_132
}  // namespace leetcode
