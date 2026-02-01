#include "leetcode/problems/find-words-containing-character.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2942 {

class FindWordsContainingCharacterTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindWordsContainingCharacterSolution solution;
};

TEST_P(FindWordsContainingCharacterTest, Example1) {
  vector<string> words = {"leet", "code"};
  char x = 'e';
  vector<int> expected = {0, 1};
  vector<int> result = solution.findWordsContaining(words, x);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(FindWordsContainingCharacterTest, Example2) {
  vector<string> words = {"abc", "bcd", "aaaa", "cbc"};
  char x = 'a';
  vector<int> expected = {0, 2};
  vector<int> result = solution.findWordsContaining(words, x);
  sort(result.begin(), result.end());
  sort(expected.begin(), expected.end());
  EXPECT_EQ(expected, result);
}

TEST_P(FindWordsContainingCharacterTest, Example3) {
  vector<string> words = {"abc", "bcd", "aaaa", "cbc"};
  char x = 'z';
  vector<int> expected = {};
  vector<int> result = solution.findWordsContaining(words, x);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindWordsContainingCharacterTest,
    ::testing::ValuesIn(FindWordsContainingCharacterSolution().getStrategyNames()));

}  // namespace problem_2942
}  // namespace leetcode