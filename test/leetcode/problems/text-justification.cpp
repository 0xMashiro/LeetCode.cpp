#include "leetcode/problems/text-justification.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_68 {

class TextJustificationTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TextJustificationSolution solution;
};

TEST_P(TextJustificationTest, Example1) {
  vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
  int maxWidth = 16;
  vector<string> expected = {
    "This    is    an",
    "example  of text",
    "justification.  "
  };
  vector<string> result = solution.fullJustify(words, maxWidth);
  EXPECT_EQ(expected, result);
}

TEST_P(TextJustificationTest, Example2) {
  vector<string> words = {"What", "must", "be", "acknowledgment", "shall", "be"};
  int maxWidth = 16;
  vector<string> expected = {
    "What   must   be",
    "acknowledgment  ",
    "shall be        "
  };
  vector<string> result = solution.fullJustify(words, maxWidth);
  EXPECT_EQ(expected, result);
}

TEST_P(TextJustificationTest, Example3) {
  vector<string> words = {"Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"};
  int maxWidth = 20;
  vector<string> expected = {
    "Science  is  what we",
    "understand      well",
    "enough to explain to",
    "a  computer.  Art is",
    "everything  else  we",
    "do                  "
  };
  vector<string> result = solution.fullJustify(words, maxWidth);
  EXPECT_EQ(expected, result);
}

TEST_P(TextJustificationTest, SingleWord) {
  vector<string> words = {"Hello"};
  int maxWidth = 10;
  vector<string> expected = {"Hello     "};
  vector<string> result = solution.fullJustify(words, maxWidth);
  EXPECT_EQ(expected, result);
}

TEST_P(TextJustificationTest, TwoWordsLastLine) {
  vector<string> words = {"hello", "world"};
  int maxWidth = 11;
  vector<string> expected = {"hello world"};
  vector<string> result = solution.fullJustify(words, maxWidth);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TextJustificationTest,
    ::testing::ValuesIn(TextJustificationSolution().getStrategyNames()));

}  // namespace problem_68
}  // namespace leetcode
