#include "leetcode/problems/count-different-palindromic-subsequences.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_730 {

class CountDifferentPalindromicSubsequencesTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountDifferentPalindromicSubsequencesSolution solution;
};

TEST_P(CountDifferentPalindromicSubsequencesTest, Example1) {
  string s = "bccb";
  int expected = 6;  // 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

TEST_P(CountDifferentPalindromicSubsequencesTest, Example2) {
  string s = "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba";
  int expected = 104860361;
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

TEST_P(CountDifferentPalindromicSubsequencesTest, SingleChar) {
  string s = "a";
  int expected = 1;  // 'a'
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

TEST_P(CountDifferentPalindromicSubsequencesTest, TwoSameChars) {
  string s = "aa";
  int expected = 2;  // 'a', 'aa'
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

TEST_P(CountDifferentPalindromicSubsequencesTest, TwoDifferentChars) {
  string s = "ab";
  int expected = 2;  // 'a', 'b'
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

TEST_P(CountDifferentPalindromicSubsequencesTest, ThreeSameChars) {
  string s = "aaa";
  int expected = 3;  // 'a', 'aa', 'aaa'
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

TEST_P(CountDifferentPalindromicSubsequencesTest, SimplePalindrome) {
  string s = "aba";
  int expected = 4;  // 'a', 'b', 'aa', 'aba'
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

TEST_P(CountDifferentPalindromicSubsequencesTest, AllSame) {
  string s = "aaaa";
  int expected = 4;  // 'a', 'aa', 'aaa', 'aaaa'
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

TEST_P(CountDifferentPalindromicSubsequencesTest, NoPalindromeExceptSingle) {
  string s = "abc";
  int expected = 3;  // 'a', 'b', 'c'
  EXPECT_EQ(expected, solution.countPalindromicSubsequences(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountDifferentPalindromicSubsequencesTest,
    ::testing::ValuesIn(CountDifferentPalindromicSubsequencesSolution().getStrategyNames()));

}  // namespace problem_730
}  // namespace leetcode
