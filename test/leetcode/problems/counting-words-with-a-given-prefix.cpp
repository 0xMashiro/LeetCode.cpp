#include "leetcode/problems/counting-words-with-a-given-prefix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2185 {

class CountingWordsWithAGivenPrefixTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountingWordsWithAGivenPrefixSolution solution;
};

TEST_P(CountingWordsWithAGivenPrefixTest, Example1) {
  vector<string> words = {"pay", "attention", "practice", "attend"};
  string pref = "at";
  int expected = 2;
  EXPECT_EQ(expected, solution.prefixCount(words, pref));
}

TEST_P(CountingWordsWithAGivenPrefixTest, Example2) {
  vector<string> words = {"leetcode", "win", "loops", "success"};
  string pref = "code";
  int expected = 0;
  EXPECT_EQ(expected, solution.prefixCount(words, pref));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountingWordsWithAGivenPrefixTest,
    ::testing::ValuesIn(CountingWordsWithAGivenPrefixSolution().getStrategyNames()));

}  // namespace problem_2185
}  // namespace leetcode
