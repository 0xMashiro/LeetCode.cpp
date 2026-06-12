#include "leetcode/problems/number-of-ways-to-assign-edge-weights-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3559 {

class NumberOfWaysToAssignEdgeWeightsIiTest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfWaysToAssignEdgeWeightsIiSolution solution;
};

TEST_P(NumberOfWaysToAssignEdgeWeightsIiTest, Example1) {
  vector<vector<int>> edges = {{1, 2}};
  vector<vector<int>> queries = {{1, 1}, {1, 2}};
  vector<int> expected = {0, 1};
  EXPECT_EQ(expected, solution.assignEdgeWeights(edges, queries));
}

TEST_P(NumberOfWaysToAssignEdgeWeightsIiTest, Example2) {
  vector<vector<int>> edges = {{1, 2}, {1, 3}, {3, 4}, {3, 5}};
  vector<vector<int>> queries = {{1, 4}, {3, 4}, {2, 5}};
  vector<int> expected = {2, 1, 4};
  EXPECT_EQ(expected, solution.assignEdgeWeights(edges, queries));
}

TEST_P(NumberOfWaysToAssignEdgeWeightsIiTest, SelfAuthoredSingleEdge) {
  // 两个节点一条边，u != v 时 L=1，答案是 1
  vector<vector<int>> edges = {{1, 2}};
  vector<vector<int>> queries = {{2, 1}};
  vector<int> expected = {1};
  EXPECT_EQ(expected, solution.assignEdgeWeights(edges, queries));
}

TEST_P(NumberOfWaysToAssignEdgeWeightsIiTest, SelfAuthoredLineTree) {
  // 链状树 1-2-3-4，测试不同距离
  vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}};
  vector<vector<int>> queries = {
      {1, 4},  // L=3, 2^(3-1)=4
      {1, 3},  // L=2, 2^(2-1)=2
      {2, 4},  // L=2, 2^(2-1)=2
      {2, 2},  // L=0, 0
      {1, 2}   // L=1, 2^(1-1)=1
  };
  vector<int> expected = {4, 2, 2, 0, 1};
  EXPECT_EQ(expected, solution.assignEdgeWeights(edges, queries));
}

TEST_P(NumberOfWaysToAssignEdgeWeightsIiTest, SelfAuthoredStarTree) {
  // 星型树：1 连接 2,3,4,5
  vector<vector<int>> edges = {{1, 2}, {1, 3}, {1, 4}, {1, 5}};
  vector<vector<int>> queries = {
      {2, 3},  // 2-1-3, L=2, 2^(2-1)=2
      {2, 4},  // 2-1-4, L=2, 2
      {2, 2},  // 0
      {2, 5}   // 2-1-5, L=2, 2
  };
  vector<int> expected = {2, 2, 0, 2};
  EXPECT_EQ(expected, solution.assignEdgeWeights(edges, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfWaysToAssignEdgeWeightsIiTest,
    ::testing::ValuesIn(NumberOfWaysToAssignEdgeWeightsIiSolution()
                            .getStrategyNames()));

}  // namespace problem_3559
}  // namespace leetcode
