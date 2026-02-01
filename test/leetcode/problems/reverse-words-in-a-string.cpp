#include "leetcode/problems/reverse-words-in-a-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_151 {

class ReverseWordsInAStringTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ReverseWordsInAStringSolution solution;
};

TEST_P(ReverseWordsInAStringTest, Example1) {
  string s = "the sky is blue";
  string expected = "blue is sky the";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, Example2) {
  string s = "  hello world  ";
  string expected = "world hello";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, Example3) {
  string s = "a good   example";
  string expected = "example good a";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, SingleWord) {
  string s = "hello";
  string expected = "hello";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, SingleWordWithSpaces) {
  string s = "  hello  ";
  string expected = "hello";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, MultipleSpacesBetweenWords) {
  string s = "a   b   c";
  string expected = "c b a";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, OnlySpaces) {
  string s = "     ";
  string expected = "";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, LeadingSpaces) {
  string s = "   leading";
  string expected = "leading";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, TrailingSpaces) {
  string s = "trailing   ";
  string expected = "trailing";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

TEST_P(ReverseWordsInAStringTest, TwoWords) {
  string s = "word1 word2";
  string expected = "word2 word1";
  EXPECT_EQ(expected, solution.reverseWords(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ReverseWordsInAStringTest,
    ::testing::ValuesIn(ReverseWordsInAStringSolution().getStrategyNames()));

}  // namespace problem_151
}  // namespace leetcode
