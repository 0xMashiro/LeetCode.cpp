#include "leetcode/problems/sum-of-prefix-scores-of-strings.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2416 {

class SumOfPrefixScoresOfStringsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SumOfPrefixScoresOfStringsSolution solution;
};

TEST_P(SumOfPrefixScoresOfStringsTest, Example1) {
  vector<string> words = {"abc","ab","bc","b"};
  vector<int> expected = {5,4,3,2};
  EXPECT_EQ(expected, solution.sumPrefixScores(words));
}

TEST_P(SumOfPrefixScoresOfStringsTest, Example2) {
  vector<string> words = {"abcd"};
  vector<int> expected = {4};
  EXPECT_EQ(expected, solution.sumPrefixScores(words));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SumOfPrefixScoresOfStringsTest,
    ::testing::ValuesIn(SumOfPrefixScoresOfStringsSolution().getStrategyNames()));

}  // namespace problem_2416
}  // namespace leetcode
