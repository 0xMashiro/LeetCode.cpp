#include "leetcode/problems/number-of-strings-that-appear-as-substrings-in-word.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1967 {

class NumberOfStringsThatAppearAsSubstringsInWordTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfStringsThatAppearAsSubstringsInWordSolution solution;
};

TEST_P(NumberOfStringsThatAppearAsSubstringsInWordTest, Example1) {
  std::vector<std::string> patterns = {"a", "abc", "bc", "d"};
  std::string word = "abc";
  int expected = 3;
  EXPECT_EQ(expected, solution.numOfStrings(patterns, word));
}

TEST_P(NumberOfStringsThatAppearAsSubstringsInWordTest, Example2) {
  std::vector<std::string> patterns = {"a", "b", "c"};
  std::string word = "aaaaabbbbb";
  int expected = 2;
  EXPECT_EQ(expected, solution.numOfStrings(patterns, word));
}

TEST_P(NumberOfStringsThatAppearAsSubstringsInWordTest, Example3) {
  std::vector<std::string> patterns = {"a", "a", "a"};
  std::string word = "ab";
  int expected = 3;
  EXPECT_EQ(expected, solution.numOfStrings(patterns, word));
}

TEST_P(NumberOfStringsThatAppearAsSubstringsInWordTest, SelfAuthoredNoMatch) {
  std::vector<std::string> patterns = {"xyz", "zzz"};
  std::string word = "abc";
  int expected = 0;
  EXPECT_EQ(expected, solution.numOfStrings(patterns, word));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfStringsThatAppearAsSubstringsInWordTest,
    ::testing::ValuesIn(
        NumberOfStringsThatAppearAsSubstringsInWordSolution()
            .getStrategyNames()));

}  // namespace problem_1967
}  // namespace leetcode
