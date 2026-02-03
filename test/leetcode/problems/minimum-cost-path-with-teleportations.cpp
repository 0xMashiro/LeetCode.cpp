#include "leetcode/problems/minimum-cost-path-with-teleportations.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3651 {

class MinimumCostPathWithTeleportationsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostPathWithTeleportationsSolution solution;
};

TEST_P(MinimumCostPathWithTeleportationsTest, Example1) {
  vector<vector<int>> grid = {{1,3,3},{2,5,4},{4,3,5}};
  int k = 2;
  int expected = 7;
  EXPECT_EQ(expected, solution.minCost(grid, k));
}

TEST_P(MinimumCostPathWithTeleportationsTest, Example2) {
  vector<vector<int>> grid = {{1,2},{2,3},{3,4}};
  int k = 1;
  int expected = 9;
  EXPECT_EQ(expected, solution.minCost(grid, k));
}


// LeetCode 失败用例: WrongAnswerCase1
TEST_P(MinimumCostPathWithTeleportationsTest, WrongAnswerCase1) {
  // 输入: grid = [[3,1],[10,4]], k = 7
    // 期望: 4
    vector<vector<int>> grid = {{3, 1}, {10, 4}};
    int k = 7;
    int expected = 4;
    EXPECT_EQ(expected, solution.minCost(grid, k));
}
INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostPathWithTeleportationsTest,
    ::testing::ValuesIn(MinimumCostPathWithTeleportationsSolution().getStrategyNames()));

}  // namespace problem_3651
}  // namespace leetcode
