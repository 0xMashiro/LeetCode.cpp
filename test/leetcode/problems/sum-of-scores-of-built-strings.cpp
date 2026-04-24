#include "leetcode/problems/sum-of-scores-of-built-strings.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2223 {

class SumOfScoresOfBuiltStringsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SumOfScoresOfBuiltStringsSolution solution;
};

TEST_P(SumOfScoresOfBuiltStringsTest, Example1) {
  string s = "babab";
  long expected = 9;
  EXPECT_EQ(expected, solution.sumScores(s));
}

TEST_P(SumOfScoresOfBuiltStringsTest, Example2) {
  string s = "azbazbzaz";
  long expected = 14;
  EXPECT_EQ(expected, solution.sumScores(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SumOfScoresOfBuiltStringsTest,
    ::testing::ValuesIn(SumOfScoresOfBuiltStringsSolution().getStrategyNames()));

}  // namespace problem_2223
}  // namespace leetcode
