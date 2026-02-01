#include "leetcode/problems/minimum-moves-to-spread-stones-over-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2850 {

class MinimumMovesToSpreadStonesOverGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumMovesToSpreadStonesOverGridSolution solution;
};

// 示例 1: grid = [[1,1,0],[1,1,1],[1,2,1]], 输出: 3
TEST_P(MinimumMovesToSpreadStonesOverGridTest, Example1) {
  vector<vector<int>> grid = {
    {1, 1, 0},
    {1, 1, 1},
    {1, 2, 1}
  };
  EXPECT_EQ(solution.minimumMoves(grid), 3);
}

// 示例 2: grid = [[1,3,0],[1,0,0],[1,0,3]], 输出: 4
TEST_P(MinimumMovesToSpreadStonesOverGridTest, Example2) {
  vector<vector<int>> grid = {
    {1, 3, 0},
    {1, 0, 0},
    {1, 0, 3}
  };
  EXPECT_EQ(solution.minimumMoves(grid), 4);
}

// 边界情况：已经是均匀分布
TEST_P(MinimumMovesToSpreadStonesOverGridTest, AlreadyUniform) {
  vector<vector<int>> grid = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  };
  EXPECT_EQ(solution.minimumMoves(grid), 0);
}

// 边界情况：所有石头在一个格子
// 从 (0,0) 到各格子的距离：0,1,2,1,2,3,2,3,4
// 需要移动 8 个石头（保留 1 个在原地）
// 最小距离和：1+1+2+2+2+3+3+4 = 18
TEST_P(MinimumMovesToSpreadStonesOverGridTest, AllInOneCell) {
  vector<vector<int>> grid = {
    {9, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  };
  EXPECT_EQ(solution.minimumMoves(grid), 18);
}

// 边界情况：多个石头在角落
// 从(0,0)多出4个，从(1,1)多出3个，需要填满8个空位
// 最优分配：(0,0)负责较近的格子，(1,1)负责较近的格子
TEST_P(MinimumMovesToSpreadStonesOverGridTest, MultipleInCorner) {
  vector<vector<int>> grid = {
    {5, 0, 0},
    {0, 4, 0},
    {0, 0, 0}
  };
  EXPECT_EQ(solution.minimumMoves(grid), 10);
}

// 边界情况：分散但非均匀
// 源：(0,0)多余1, (0,1)多余1, (0,2)多余1
// 目标：(2,0), (2,1), (2,2)
// 最优：(0,0)->(2,0)=2, (0,1)->(2,1)=2, (0,2)->(2,2)=2, 总和=6
TEST_P(MinimumMovesToSpreadStonesOverGridTest, ScatteredNonUniform) {
  vector<vector<int>> grid = {
    {2, 2, 2},
    {1, 1, 1},
    {0, 0, 0}
  };
  EXPECT_EQ(solution.minimumMoves(grid), 6);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, 
    MinimumMovesToSpreadStonesOverGridTest,
    ::testing::ValuesIn(MinimumMovesToSpreadStonesOverGridSolution().getStrategyNames()));

}  // namespace problem_2850
}  // namespace leetcode
