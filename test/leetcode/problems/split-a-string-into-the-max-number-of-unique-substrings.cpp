#include "leetcode/problems/split-a-string-into-the-max-number-of-unique-substrings.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1593 {

class SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SplitAStringIntoTheMaxNumberOfUniqueSubstringsSolution solution;
};

TEST_P(SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest, Example1) {
  string s = "ababccc";
  int expected = 5;
  EXPECT_EQ(expected, solution.maxUniqueSplit(s));
}

TEST_P(SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest, Example2) {
  string s = "aba";
  int expected = 2;
  EXPECT_EQ(expected, solution.maxUniqueSplit(s));
}

TEST_P(SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest, Example3) {
  string s = "aa";
  int expected = 1;
  EXPECT_EQ(expected, solution.maxUniqueSplit(s));
}

TEST_P(SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest, SingleChar) {
  // 边界：单字符
  string s = "a";
  int expected = 1;
  EXPECT_EQ(expected, solution.maxUniqueSplit(s));
}

TEST_P(SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest, AllUniqueChars) {
  // 边界：所有字符都不同，可以拆分为单个字符
  string s = "abcdef";
  int expected = 6;
  EXPECT_EQ(expected, solution.maxUniqueSplit(s));
}

TEST_P(SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest, TwoSameChars) {
  // 边界：两个相同字符，只能作为一个整体
  string s = "aa";
  int expected = 1;
  EXPECT_EQ(expected, solution.maxUniqueSplit(s));
}

TEST_P(SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest, FourSameChars) {
  // "aaaa" 可以拆分为 ["a", "aaa"] 或 ["aaa", "a"]，数量为 2
  string s = "aaaa";
  int expected = 2;
  EXPECT_EQ(expected, solution.maxUniqueSplit(s));
}

TEST_P(SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest, ComplexCase1) {
  // 额外测试：复杂情况
  string s = "wwwzfvedwzfhsww";
  int expected = 11;
  EXPECT_EQ(expected, solution.maxUniqueSplit(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SplitAStringIntoTheMaxNumberOfUniqueSubstringsTest,
    ::testing::ValuesIn(SplitAStringIntoTheMaxNumberOfUniqueSubstringsSolution().getStrategyNames()));

}  // namespace problem_1593
}  // namespace leetcode
