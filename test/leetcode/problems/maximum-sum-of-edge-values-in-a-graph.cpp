#include "leetcode/problems/maximum-sum-of-edge-values-in-a-graph.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3547 {

class MaximumSumOfEdgeValuesInAGraphTest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumSumOfEdgeValuesInAGraphSolution solution;
};

// Example 1: n=4, 路径 [[0,1],[1,2],[2,3]]
TEST_P(MaximumSumOfEdgeValuesInAGraphTest, Example1) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}};
  long long expected = 23;
  EXPECT_EQ(expected, solution.maxScore(n, edges));
}

// Example 2: n=6, 环 [[0,3],[4,5],[2,0],[1,3],[2,4],[1,5]]
TEST_P(MaximumSumOfEdgeValuesInAGraphTest, Example2) {
  int n = 6;
  vector<vector<int>> edges = {{0, 3}, {4, 5}, {2, 0}, {1, 3}, {2, 4}, {1, 5}};
  long long expected = 82;
  EXPECT_EQ(expected, solution.maxScore(n, edges));
}

// 自编边界：n=1, 单节点（边数 m=0? 不对，约束 m>=1, 且图连通）
// 最小连通图：n=2, 一条边
TEST_P(MaximumSumOfEdgeValuesInAGraphTest, SelfAuthoredTwoNodes) {
  int n = 2;
  vector<vector<int>> edges = {{0, 1}};
  // 只有两个节点，值只能分配 1 和 2
  // 边和 = 1*2 = 2
  long long expected = 2;
  EXPECT_EQ(expected, solution.maxScore(n, edges));
}

// 自编：n=3, 路径
TEST_P(MaximumSumOfEdgeValuesInAGraphTest, SelfAuthoredThreeNodes) {
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {1, 2}};
  // 值 1,2,3 排列。最优排列: [1,3,2] 或 [2,3,1]
  // 边和 = 1*3 + 3*2 = 3+6 = 9
  long long expected = 9;
  EXPECT_EQ(expected, solution.maxScore(n, edges));
}

// 自编：n=5, 路径
TEST_P(MaximumSumOfEdgeValuesInAGraphTest, SelfAuthoredPath5) {
  int n = 5;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
  // 排列: [1,3,5,4,2] 边和 = 1*3+3*5+5*4+4*2 = 3+15+20+8 = 46
  long long expected = 46;
  EXPECT_EQ(expected, solution.maxScore(n, edges));
}

// 自编：n=4, 环
TEST_P(MaximumSumOfEdgeValuesInAGraphTest, SelfAuthoredCycle4) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};
  // 排列: [1,3,4,2] 边和(环) = 1*3+3*4+4*2+2*1 = 3+12+8+2 = 25
  long long expected = 25;
  EXPECT_EQ(expected, solution.maxScore(n, edges));
}

// 自编：n=7, 路径
TEST_P(MaximumSumOfEdgeValuesInAGraphTest, SelfAuthoredPath7) {
  int n = 7;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}};
  // 排列: [1,3,5,7,6,4,2]
  // 边和 = 1*3+3*5+5*7+7*6+6*4+4*2 = 3+15+35+42+24+8 = 127
  long long expected = 127;
  EXPECT_EQ(expected, solution.maxScore(n, edges));
}

// 自编：n=8, 环
TEST_P(MaximumSumOfEdgeValuesInAGraphTest, SelfAuthoredCycle8) {
  int n = 8;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}, {3, 4},
                               {4, 5}, {5, 6}, {6, 7}, {7, 0}};
  // 排列: [1,3,5,7,8,6,4,2]
  // 路径边和 = 1*3+3*5+5*7+7*8+8*6+6*4+4*2 = 3+15+35+56+48+24+8 = 189
  // 环边和 = 189 + 2*1 = 191
  long long expected = 191;
  EXPECT_EQ(expected, solution.maxScore(n, edges));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumSumOfEdgeValuesInAGraphTest,
    ::testing::ValuesIn(MaximumSumOfEdgeValuesInAGraphSolution().getStrategyNames()));

}  // namespace problem_3547
}  // namespace leetcode
