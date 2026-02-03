
#include "leetcode/problems/path-with-maximum-probability.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1514 {

class PathWithMaximumProbabilityTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PathWithMaximumProbabilitySolution solution;
};

TEST_P(PathWithMaximumProbabilityTest, Example1) {
  // Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
  // Output: 0.25000
  // Explanation: Two paths: 0->2 (prob=0.2) or 0->1->2 (prob=0.5*0.5=0.25)
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {0, 2}};
  vector<double> succProb = {0.5, 0.5, 0.2};
  int start_node = 0;
  int end_node = 2;
  double result = solution.maxProbability(n, edges, succProb, start_node, end_node);
  EXPECT_NEAR(result, 0.25, 1e-5);
}

TEST_P(PathWithMaximumProbabilityTest, Example2) {
  // Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
  // Output: 0.30000
  // Explanation: Direct path 0->2 has prob 0.3, which is better than 0->1->2 (0.25)
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {0, 2}};
  vector<double> succProb = {0.5, 0.5, 0.3};
  int start_node = 0;
  int end_node = 2;
  double result = solution.maxProbability(n, edges, succProb, start_node, end_node);
  EXPECT_NEAR(result, 0.3, 1e-5);
}

TEST_P(PathWithMaximumProbabilityTest, Example3) {
  // Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
  // Output: 0.00000
  // Explanation: No path between 0 and 2
  int n = 3;
  vector<vector<int>> edges = {{0, 1}};
  vector<double> succProb = {0.5};
  int start_node = 0;
  int end_node = 2;
  double result = solution.maxProbability(n, edges, succProb, start_node, end_node);
  EXPECT_NEAR(result, 0.0, 1e-5);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PathWithMaximumProbabilityTest,
    ::testing::ValuesIn(PathWithMaximumProbabilitySolution().getStrategyNames()));

}  // namespace problem_1514
}  // namespace leetcode
