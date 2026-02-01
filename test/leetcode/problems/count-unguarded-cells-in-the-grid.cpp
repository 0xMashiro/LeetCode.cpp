#include "leetcode/problems/count-unguarded-cells-in-the-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2257 {

class CountUnguardedCellsInTheGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountUnguardedCellsInTheGridSolution solution;
};

TEST_P(CountUnguardedCellsInTheGridTest, Example1) {
  int m = 4, n = 6;
  vector<vector<int>> guards = {{0, 0}, {1, 1}, {2, 3}};
  vector<vector<int>> walls = {{0, 1}, {2, 2}, {1, 4}};
  EXPECT_EQ(7, solution.countUnguarded(m, n, guards, walls));
}

TEST_P(CountUnguardedCellsInTheGridTest, Example2) {
  int m = 3, n = 3;
  vector<vector<int>> guards = {{1, 1}};
  vector<vector<int>> walls = {{0, 1}, {1, 0}, {2, 1}, {1, 2}};
  EXPECT_EQ(4, solution.countUnguarded(m, n, guards, walls));
}

TEST_P(CountUnguardedCellsInTheGridTest, SingleGuardNoWalls) {
  // 2x2 网格，警卫在 (0,0)
  // 警卫能看到 (0,1) 和 (1,0)，但看不到对角线 (1,1)
  // 所以 (1,1) 是未被保卫的
  int m = 2, n = 2;
  vector<vector<int>> guards = {{0, 0}};
  vector<vector<int>> walls = {};
  EXPECT_EQ(1, solution.countUnguarded(m, n, guards, walls));
}

TEST_P(CountUnguardedCellsInTheGridTest, AllWalls) {
  // 所有非警卫位置都是墙，没有被保卫的格子需要计算
  int m = 2, n = 2;
  vector<vector<int>> guards = {{0, 0}};
  vector<vector<int>> walls = {{0, 1}, {1, 0}, {1, 1}};
  EXPECT_EQ(0, solution.countUnguarded(m, n, guards, walls));
}

TEST_P(CountUnguardedCellsInTheGridTest, GuardBlockedByWall) {
  // 3x3 网格，警卫在 (0,0)，墙在 (0,1)
  // 向东被墙挡住，向南可以看到 (1,0) 和 (2,0)
  // 被保卫的格子: 2个，警卫: 1个，墙: 1个
  // 未被保卫的: 9 - 1 - 1 - 2 = 5个
  int m = 3, n = 3;
  vector<vector<int>> guards = {{0, 0}};
  vector<vector<int>> walls = {{0, 1}};
  EXPECT_EQ(5, solution.countUnguarded(m, n, guards, walls));
}

TEST_P(CountUnguardedCellsInTheGridTest, MultipleGuardsBlockEachOther) {
  // 3x3 网格，两个警卫在 (0,0) 和 (0,2)
  // 警卫(0,0)向东能看到(0,1)，被警卫(0,2)挡住；向南能看到(1,0),(2,0)
  // 警卫(0,2)向西能看到(0,1)，被警卫(0,0)挡住；向南能看到(1,2),(2,2)
  // 被保卫的格子: (0,1), (1,0), (2,0), (1,2), (2,2) = 5个
  // 警卫: 2个，未被保卫的: 9 - 2 - 5 = 2个 (即(1,1)和其他一个...不对)
  // 实际未被保卫的: (1,1) 只有1个
  int m = 3, n = 3;
  vector<vector<int>> guards = {{0, 0}, {0, 2}};
  vector<vector<int>> walls = {};
  EXPECT_EQ(2, solution.countUnguarded(m, n, guards, walls));
}

TEST_P(CountUnguardedCellsInTheGridTest, MinimalGrid) {
  // 最小的网格 1x2
  int m = 1, n = 2;
  vector<vector<int>> guards = {{0, 0}};
  vector<vector<int>> walls = {};
  EXPECT_EQ(0, solution.countUnguarded(m, n, guards, walls));
}

TEST_P(CountUnguardedCellsInTheGridTest, GuardCannotSeeThroughGuard) {
  // 两个警卫在同一行，中间的格子被第一个警卫看到，但第二个警卫挡住继续传播
  int m = 1, n = 5;
  vector<vector<int>> guards = {{0, 0}, {0, 4}};
  vector<vector<int>> walls = {};
  // (0,1), (0,2), (0,3) 都被保卫，没有未被保卫的格子
  EXPECT_EQ(0, solution.countUnguarded(m, n, guards, walls));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountUnguardedCellsInTheGridTest,
    ::testing::ValuesIn(CountUnguardedCellsInTheGridSolution().getStrategyNames()));

}  // namespace problem_2257
}  // namespace leetcode
