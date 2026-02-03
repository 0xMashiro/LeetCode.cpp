#include "leetcode/problems/max-area-of-island.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_695 {

class MaxAreaOfIslandTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaxAreaOfIslandSolution solution;
};

TEST_P(MaxAreaOfIslandTest, Example1) {
  vector<vector<int>> grid = {
    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
  };
  EXPECT_EQ(6, solution.maxAreaOfIsland(grid));
}

TEST_P(MaxAreaOfIslandTest, Example2) {
  vector<vector<int>> grid = {{0, 0, 0, 0, 0, 0, 0, 0}};
  EXPECT_EQ(0, solution.maxAreaOfIsland(grid));
}

TEST_P(MaxAreaOfIslandTest, SingleCellIsland) {
  vector<vector<int>> grid = {{1}};
  EXPECT_EQ(1, solution.maxAreaOfIsland(grid));
}

TEST_P(MaxAreaOfIslandTest, AllWater) {
  vector<vector<int>> grid = {{0, 0}, {0, 0}};
  EXPECT_EQ(0, solution.maxAreaOfIsland(grid));
}

TEST_P(MaxAreaOfIslandTest, AllLand) {
  vector<vector<int>> grid = {{1, 1}, {1, 1}};
  EXPECT_EQ(4, solution.maxAreaOfIsland(grid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaxAreaOfIslandTest,
    ::testing::ValuesIn(MaxAreaOfIslandSolution().getStrategyNames()));

}  // namespace problem_695
}  // namespace leetcode
