#include "leetcode/problems/minimum-cost-path-with-edge-reversals.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3650 {

class MinimumCostPathWithEdgeReversalsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostPathWithEdgeReversalsSolution solution;
};

TEST_P(MinimumCostPathWithEdgeReversalsTest, Example1) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1, 3}, {3, 1, 1}, {2, 3, 4}, {0, 2, 2}};
  int expected = 5;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostPathWithEdgeReversalsTest, Example2) {
  int n = 4;
  vector<vector<int>> edges = {{0, 2, 1}, {2, 1, 1}, {1, 3, 1}, {2, 3, 3}};
  int expected = 3;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostPathWithEdgeReversalsTest, SmallGraphWithReversal) {
  int n = 3;
  vector<vector<int>> edges = {{0, 1, 1}, {2, 1, 2}};
  // 0 -> 1 (cost 1), at node 1 reverse edge 2->1 to 1->2 (cost 4), total 5
  int expected = 5;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostPathWithEdgeReversalsTest, DirectEdge) {
  int n = 2;
  vector<vector<int>> edges = {{0, 1, 5}};
  int expected = 5;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostPathWithEdgeReversalsTest, NoPath) {
  int n = 3;
  vector<vector<int>> edges = {{1, 2, 1}};
  // No edge from 0, cannot reach node 2
  int expected = -1;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostPathWithEdgeReversalsTest, UseReversalToReachTarget) {
  int n = 3;
  vector<vector<int>> edges = {{0, 1, 1}, {2, 1, 2}};
  // Same as SmallGraphWithReversal, already tested
  int expected = 5;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostPathWithEdgeReversalsTest, MultipleReversalsPossible) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1, 1}, {2, 1, 1}, {3, 2, 1}};
  // Path: 0->1 (1), at node 1 reverse edge 2->1 to 1->2 (2), then at node 2 reverse edge 3->2 to 2->3 (2), total 5
  int expected = 5;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostPathWithEdgeReversalsTest, ThreeReversalsNeeded) {
  int n = 5;
  vector<vector<int>> edges = {{0, 1, 1}, {2, 1, 1}, {3, 2, 1}, {4, 3, 1}};
  // Path: 0->1 (1), reverse 2->1 to 1->2 (2), reverse 3->2 to 2->3 (2), reverse 4->3 to 3->4 (2), total 7
  // With MAX_SWITCH=100, should find path.
  int expected = 7;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

TEST_P(MinimumCostPathWithEdgeReversalsTest, ManyReversalsRequired) {
  int n = 10;
  vector<vector<int>> edges;
  // Only one forward edge from 0 to 1, all others are incoming edges for reversal
  edges.push_back({0, 1, 1});
  for (int i = 2; i < n; ++i) {
    edges.push_back({i, i-1, 1});  // edge i -> i-1, can be reversed at node i-1
  }
  // Path: 0->1 (1), then at each node i (1..8) reverse edge (i+1,i) to go to i+1, cost 2 each.
  // Total cost: 1 + 2*8 = 17
  int expected = 17;
  int result = solution.minCost(n, edges);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostPathWithEdgeReversalsTest,
    ::testing::ValuesIn(MinimumCostPathWithEdgeReversalsSolution().getStrategyNames()));

}  // namespace problem_3650
}  // namespace leetcode