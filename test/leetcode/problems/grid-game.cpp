#include "leetcode/problems/grid-game.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2017 {

class GridGameTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  GridGameSolution solution;
};

TEST_P(GridGameTest, Example1) {
  // Input: grid = [[2,5,4],[1,5,1]]
  // Output: 4
  vector<vector<int>> grid = {{2, 5, 4}, {1, 5, 1}};
  EXPECT_EQ(4, solution.gridGame(grid));
}

TEST_P(GridGameTest, Example2) {
  // Input: grid = [[3,3,1],[8,5,2]]
  // Output: 4
  vector<vector<int>> grid = {{3, 3, 1}, {8, 5, 2}};
  EXPECT_EQ(4, solution.gridGame(grid));
}

TEST_P(GridGameTest, Example3) {
  // Input: grid = [[1,3,1,15],[1,3,3,1]]
  // Output: 7
  vector<vector<int>> grid = {{1, 3, 1, 15}, {1, 3, 3, 1}};
  EXPECT_EQ(7, solution.gridGame(grid));
}

TEST_P(GridGameTest, SingleColumn) {
  // 边界情况：只有一列
  // 第一个机器人必须在这一列向下，第二个机器人无分可拿
  vector<vector<int>> grid = {{5}, {3}};
  EXPECT_EQ(0, solution.gridGame(grid));
}

TEST_P(GridGameTest, TwoColumns) {
  // 边界情况：两列
  vector<vector<int>> grid = {{1, 2}, {3, 4}};
  // i=0: max(0, 2) = 2
  // i=1: max(3, 0) = 3
  // min = 2
  EXPECT_EQ(2, solution.gridGame(grid));
}

TEST_P(GridGameTest, LargeValues) {
  // 测试大数值情况
  vector<vector<int>> grid = {{100000, 100000}, {100000, 100000}};
  long long result = solution.gridGame(grid);
  EXPECT_EQ(100000, result);
}

TEST_P(GridGameTest, AllZerosInOneRow) {
  // 某一行全为0的情况
  vector<vector<int>> grid = {{0, 0, 0}, {1, 2, 3}};
  // 第一个机器人应该在第2列向下，让第二个机器人只能从第二行走
  // i=2: max(1+2=3, 0) = 3
  // 但它应该更早下去以减少第二个机器人的收益
  // i=0: max(0, 0) = 0
  EXPECT_EQ(0, solution.gridGame(grid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, GridGameTest,
    ::testing::ValuesIn(GridGameSolution().getStrategyNames()));

}  // namespace problem_2017
}  // namespace leetcode
