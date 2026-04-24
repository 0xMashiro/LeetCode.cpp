#include "leetcode/problems/maximum-profit-from-valid-topological-order-in-dag.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3530 {

class MaximumProfitFromValidTopologicalOrderInDagTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumProfitFromValidTopologicalOrderInDagSolution solution;
};

// ===== Example 1 (from LeetCode) =====
// Input:  n = 2, edges = [[0,1]], score = [2,3]
// Output: 8
TEST_P(MaximumProfitFromValidTopologicalOrderInDagTest, Example1) {
  int n = 2;
  vector<vector<int>> edges = {{0, 1}};
  vector<int> score = {2, 3};
  int res = solution.maxProfit(n, edges, score);
  EXPECT_EQ(8, res);
}

// ===== Example 2 (from LeetCode) =====
// Input:  n = 3, edges = [[0,1],[0,2]], score = [1,6,3]
// Output: 25
TEST_P(MaximumProfitFromValidTopologicalOrderInDagTest, Example2) {
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {0, 2}};
  vector<int> score = {1, 6, 3};
  int res = solution.maxProfit(n, edges, score);
  EXPECT_EQ(25, res);
}

// ===== Self-authored: Single node =====
TEST_P(MaximumProfitFromValidTopologicalOrderInDagTest, SelfAuthoredSingleNode) {
  int n = 1;
  vector<vector<int>> edges = {};
  vector<int> score = {42};
  int res = solution.maxProfit(n, edges, score);
  EXPECT_EQ(42, res);
}

// ===== Self-authored: Two independent nodes =====
// Optimal: smaller score first → [0(s=5), 1(s=10)] → 5*1 + 10*2 = 25
TEST_P(MaximumProfitFromValidTopologicalOrderInDagTest, SelfAuthoredTwoIndependent) {
  int n = 2;
  vector<vector<int>> edges = {};
  vector<int> score = {5, 10};
  int res = solution.maxProfit(n, edges, score);
  EXPECT_EQ(25, res);
}

// ===== Self-authored: Chain (only one valid order) =====
TEST_P(MaximumProfitFromValidTopologicalOrderInDagTest, SelfAuthoredChain) {
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {1, 2}};
  vector<int> score = {1, 2, 3};
  int res = solution.maxProfit(n, edges, score);
  EXPECT_EQ(14, res);
}

// ===== Self-authored: Diamond =====
// n=4, edges=[[0,1],[0,2],[1,3],[2,3]], score=[5,3,4,2]
// Optimal: 0(s=5,p1), 1(s=3,p2), 2(s=4,p3), 3(s=2,p4) → 5+6+12+8=31
TEST_P(MaximumProfitFromValidTopologicalOrderInDagTest, SelfAuthoredDiamond) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
  vector<int> score = {5, 3, 4, 2};
  int res = solution.maxProfit(n, edges, score);
  EXPECT_EQ(31, res);
}

// ===== Self-authored: Complex DAG with branching =====
// n=5, edges=[[0,1],[0,2],[1,3],[2,4]], score=[10,1,100,1,50]
// Optimal order: 0(p1=10), 1(p2=2), 3(p3=3), 2(p4=400), 4(p5=250) = 665
TEST_P(MaximumProfitFromValidTopologicalOrderInDagTest, SelfAuthoredComplex) {
  int n = 5;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 4}};
  vector<int> score = {10, 1, 100, 1, 50};
  int res = solution.maxProfit(n, edges, score);
  EXPECT_EQ(665, res);
}



// LeetCode 失败用例: WrongAnswerCase1
TEST_P(MaximumProfitFromValidTopologicalOrderInDagTest, WrongAnswerCase1) {
  int n = 5;
    vector<vector<int>> edges = {{1,2},{0,3},{1,4},{2,3},{1,3}};
    vector<int> score = {50913, 47946, 97391, 27488, 69147};
    int res = solution.maxProfit(n, edges, score);
    EXPECT_EQ(897632, res);
}
INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumProfitFromValidTopologicalOrderInDagTest,
    ::testing::ValuesIn(MaximumProfitFromValidTopologicalOrderInDagSolution().getStrategyNames()));

}  // namespace problem_3530
}  // namespace leetcode
