#include "leetcode/problems/maximum-path-score-in-a-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3742 {

class MaximumPathScoreInAGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumPathScoreInAGridSolution solution;
};

TEST_P(MaximumPathScoreInAGridTest, Example1) {
  vector<vector<int>> grid = {{0, 1}, {2, 0}};
  int k = 1;
  int expected = 2;
  EXPECT_EQ(expected, solution.maxPathScore(grid, k));
}

TEST_P(MaximumPathScoreInAGridTest, Example2) {
  vector<vector<int>> grid = {{0, 1}, {1, 2}};
  int k = 1;
  int expected = -1;
  EXPECT_EQ(expected, solution.maxPathScore(grid, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumPathScoreInAGridTest,
    ::testing::ValuesIn(MaximumPathScoreInAGridSolution().getStrategyNames()));

}  // namespace problem_3742
}  // namespace leetcode
