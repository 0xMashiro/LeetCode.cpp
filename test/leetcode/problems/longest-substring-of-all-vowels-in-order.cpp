#include "leetcode/problems/longest-substring-of-all-vowels-in-order.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1839 {

class LongestSubstringOfAllVowelsInOrderTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestSubstringOfAllVowelsInOrderSolution solution;
};

TEST_P(LongestSubstringOfAllVowelsInOrderTest, Example1) {
  string word = "aeiaaioaaaaeiiiiouuuooaauuaeiu";
  EXPECT_EQ(13, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, Example2) {
  string word = "aeeeiiiioooauuuaeiou";
  EXPECT_EQ(5, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, Example3) {
  string word = "a";
  EXPECT_EQ(0, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, EmptyString) {
  string word = "";
  EXPECT_EQ(0, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, AllSameVowel) {
  // 只有 'a'，不满足所有元音的条件
  string word = "aaaaaa";
  EXPECT_EQ(0, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, ReverseOrder) {
  // 逆序排列，不满足条件
  string word = "uoiea";
  EXPECT_EQ(0, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, MinimalValid) {
  // 最短的美丽子串
  string word = "aeiou";
  EXPECT_EQ(5, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, BreakInMiddle) {
  // 中间有打断
  string word = "aaaeiouaaa";
  EXPECT_EQ(7, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, MissingOneVowel) {
  // 缺少一个元音
  string word = "aaaeeeiiiooo";
  EXPECT_EQ(0, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, LongRepeatedPattern) {
  // 长重复模式
  string word = "aaaaaaeeeeeeiiiiiioooooouuuuuu";
  EXPECT_EQ(30, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, InterleavedPattern) {
  // 中间有乱序，需要重新开始
  string word = "aeiaeiou";
  // "aeiaeiou" 中，"aeiou" 从索引3开始，长度为5
  EXPECT_EQ(5, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, ConsecutiveBeautiful) {
  // 多个连续的美丽子串，被顺序打破分隔
  string word = "aeiouaeiou";
  // 两个独立的 "aeiou"，最长为 5
  EXPECT_EQ(5, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, StartsWithNonA) {
  // 不从 'a' 开始
  string word = "eeeeiiiioooouuuu";
  EXPECT_EQ(0, solution.longestBeautifulSubstring(word));
}

TEST_P(LongestSubstringOfAllVowelsInOrderTest, OnlyU) {
  // 只有 'u'
  string word = "uuuuu";
  EXPECT_EQ(0, solution.longestBeautifulSubstring(word));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestSubstringOfAllVowelsInOrderTest,
    ::testing::ValuesIn(LongestSubstringOfAllVowelsInOrderSolution().getStrategyNames()));

}  // namespace problem_1839
}  // namespace leetcode
