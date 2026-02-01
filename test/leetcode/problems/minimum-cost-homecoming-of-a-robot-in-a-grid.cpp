
#include "leetcode/problems/minimum-cost-homecoming-of-a-robot-in-a-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2087 {

class MinimumCostHomecomingOfARobotInAGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostHomecomingOfARobotInAGridSolution solution;
};

TEST_P(MinimumCostHomecomingOfARobotInAGridTest, Example1) {
  // startPos = [1, 0], homePos = [2, 3], rowCosts = [5, 4, 3], colCosts = [8, 2, 6, 7]
  // Path: (1,0) -> down to (2,0) cost=3 -> right to (2,1) cost=2 -> right to (2,2) cost=6 -> right to (2,3) cost=7
  // Total: 3 + 2 + 6 + 7 = 18
  vector<int> startPos = {1, 0};
  vector<int> homePos = {2, 3};
  vector<int> rowCosts = {5, 4, 3};
  vector<int> colCosts = {8, 2, 6, 7};
  EXPECT_EQ(18, solution.minCost(startPos, homePos, rowCosts, colCosts));
}

TEST_P(MinimumCostHomecomingOfARobotInAGridTest, Example2) {
  // Already at home
  vector<int> startPos = {0, 0};
  vector<int> homePos = {0, 0};
  vector<int> rowCosts = {5};
  vector<int> colCosts = {26};
  EXPECT_EQ(0, solution.minCost(startPos, homePos, rowCosts, colCosts));
}

TEST_P(MinimumCostHomecomingOfARobotInAGridTest, MoveUp) {
  // startPos = [2, 0], homePos = [0, 0], rowCosts = [1, 2, 3], colCosts = {5}
  // Path: (2,0) -> up to (1,0) cost=2 -> up to (0,0) cost=1
  // Total: 2 + 1 = 3
  vector<int> startPos = {2, 0};
  vector<int> homePos = {0, 0};
  vector<int> rowCosts = {1, 2, 3};
  vector<int> colCosts = {5};
  EXPECT_EQ(3, solution.minCost(startPos, homePos, rowCosts, colCosts));
}

TEST_P(MinimumCostHomecomingOfARobotInAGridTest, MoveLeft) {
  // startPos = {0, 3}, homePos = {0, 0}, rowCosts = {5}, colCosts = {1, 2, 3, 4}
  // Path: (0,3) -> left to (0,2) cost=3 -> left to (0,1) cost=2 -> left to (0,0) cost=1
  // Total: 3 + 2 + 1 = 6
  vector<int> startPos = {0, 3};
  vector<int> homePos = {0, 0};
  vector<int> rowCosts = {5};
  vector<int> colCosts = {1, 2, 3, 4};
  EXPECT_EQ(6, solution.minCost(startPos, homePos, rowCosts, colCosts));
}

TEST_P(MinimumCostHomecomingOfARobotInAGridTest, DiagonalMove) {
  // startPos = {0, 0}, homePos = {2, 2}, rowCosts = {1, 2, 3}, colCosts = {4, 5, 6}
  // Path down then right: row 1(cost=2) + row 2(cost=3) + col 1(cost=5) + col 2(cost=6) = 16
  vector<int> startPos = {0, 0};
  vector<int> homePos = {2, 2};
  vector<int> rowCosts = {1, 2, 3};
  vector<int> colCosts = {4, 5, 6};
  EXPECT_EQ(16, solution.minCost(startPos, homePos, rowCosts, colCosts));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostHomecomingOfARobotInAGridTest,
    ::testing::ValuesIn(MinimumCostHomecomingOfARobotInAGridSolution().getStrategyNames()));

}  // namespace problem_2087
}  // namespace leetcode
