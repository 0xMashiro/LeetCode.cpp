#include "leetcode/problems/shortest-path-in-a-grid-with-obstacles-elimination.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1293 {

class ShortestPathInAGridWithObstaclesEliminationTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ShortestPathInAGridWithObstaclesEliminationSolution solution;
};

TEST_P(ShortestPathInAGridWithObstaclesEliminationTest, Example1) {
  vector<vector<int>> grid = {
    {0, 0, 0},
    {1, 1, 0},
    {0, 0, 0},
    {0, 1, 1},
    {0, 0, 0}
  };
  int k = 1;
  int expected = 6;
  EXPECT_EQ(expected, solution.shortestPath(grid, k));
}

TEST_P(ShortestPathInAGridWithObstaclesEliminationTest, Example2) {
  vector<vector<int>> grid = {
    {0, 1, 1},
    {1, 1, 1},
    {1, 0, 0}
  };
  int k = 1;
  int expected = -1;
  EXPECT_EQ(expected, solution.shortestPath(grid, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ShortestPathInAGridWithObstaclesEliminationTest,
    ::testing::ValuesIn(ShortestPathInAGridWithObstaclesEliminationSolution().getStrategyNames()));

}  // namespace problem_1293
}  // namespace leetcode
