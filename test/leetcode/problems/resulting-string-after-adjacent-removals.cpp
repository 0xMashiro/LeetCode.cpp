#include "leetcode/problems/resulting-string-after-adjacent-removals.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3561 {

class ResultingStringAfterAdjacentRemovalsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ResultingStringAfterAdjacentRemovalsSolution solution;
};

TEST_P(ResultingStringAfterAdjacentRemovalsTest, Example1) {
  string s = "abc";
  string expected = "c";
  EXPECT_EQ(expected, solution.resultingString(s));
}

TEST_P(ResultingStringAfterAdjacentRemovalsTest, Example2) {
  string s = "adcb";
  string expected = "";
  EXPECT_EQ(expected, solution.resultingString(s));
}

TEST_P(ResultingStringAfterAdjacentRemovalsTest, Example3) {
  string s = "zadb";
  string expected = "db";
  EXPECT_EQ(expected, solution.resultingString(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ResultingStringAfterAdjacentRemovalsTest,
    ::testing::ValuesIn(ResultingStringAfterAdjacentRemovalsSolution().getStrategyNames()));

}  // namespace problem_3561
}  // namespace leetcode
