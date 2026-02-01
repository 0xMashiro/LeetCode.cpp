#include "leetcode/problems/longest-subsequence-repeated-k-times.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2014 {

class LongestSubsequenceRepeatedKTimesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestSubsequenceRepeatedKTimesSolution solution;
};

TEST_P(LongestSubsequenceRepeatedKTimesTest, Example1) {
  std::string s = "letsleetcode";
  int k = 2;
  std::string expected = "let";
  EXPECT_EQ(expected, solution.longestSubsequenceRepeatedK(s, k));
}

TEST_P(LongestSubsequenceRepeatedKTimesTest, Example2) {
  std::string s = "bb";
  int k = 2;
  std::string expected = "b";
  EXPECT_EQ(expected, solution.longestSubsequenceRepeatedK(s, k));
}

TEST_P(LongestSubsequenceRepeatedKTimesTest, Example3) {
  std::string s = "ab";
  int k = 2;
  std::string expected = "";
  EXPECT_EQ(expected, solution.longestSubsequenceRepeatedK(s, k));
}

TEST_P(LongestSubsequenceRepeatedKTimesTest, SingleCharRepeated) {
  std::string s = "aaaa";
  int k = 2;
  std::string expected = "aa";
  EXPECT_EQ(expected, solution.longestSubsequenceRepeatedK(s, k));
}

TEST_P(LongestSubsequenceRepeatedKTimesTest, AllSameChar) {
  std::string s = "aaaaaa";
  int k = 3;
  std::string expected = "aa";
  EXPECT_EQ(expected, solution.longestSubsequenceRepeatedK(s, k));
}

TEST_P(LongestSubsequenceRepeatedKTimesTest, NoValidSubsequence) {
  std::string s = "abcdef";
  int k = 2;
  std::string expected = "";
  EXPECT_EQ(expected, solution.longestSubsequenceRepeatedK(s, k));
}

TEST_P(LongestSubsequenceRepeatedKTimesTest, LexicographicallyLargest) {
  // 测试字典序最大的选择
  std::string s = "zzxyyxx";
  int k = 2;
  std::string result = solution.longestSubsequenceRepeatedK(s, k);
  // "z" 只能出现 2 次，但 k=2 时 "z" 重复 2 次 = "zz"，s 中有 "zz" 吗？
  // s = "zzxyyxx"，有 "zz" 子序列，所以 "z" 可以
  EXPECT_EQ("z", result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestSubsequenceRepeatedKTimesTest,
    ::testing::ValuesIn(LongestSubsequenceRepeatedKTimesSolution().getStrategyNames()));

}  // namespace problem_2014
}  // namespace leetcode
