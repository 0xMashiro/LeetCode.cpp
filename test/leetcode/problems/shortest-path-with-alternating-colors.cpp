
#include "leetcode/problems/shortest-path-with-alternating-colors.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1129 {

class ShortestPathWithAlternatingColorsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ShortestPathWithAlternatingColorsSolution solution;
};

// Example 1: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
// Output: [0,1,-1]
TEST_P(ShortestPathWithAlternatingColorsTest, Example1) {
  int n = 3;
  vector<vector<int>> redEdges = {{0, 1}, {1, 2}};
  vector<vector<int>> blueEdges = {};
  vector<int> expected = {0, 1, -1};
  vector<int> result = solution.shortestAlternatingPaths(n, redEdges, blueEdges);
  EXPECT_EQ(expected, result);
}

// Example 2: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
// Output: [0,1,-1]
TEST_P(ShortestPathWithAlternatingColorsTest, Example2) {
  int n = 3;
  vector<vector<int>> redEdges = {{0, 1}};
  vector<vector<int>> blueEdges = {{2, 1}};
  vector<int> expected = {0, 1, -1};
  vector<int> result = solution.shortestAlternatingPaths(n, redEdges, blueEdges);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ShortestPathWithAlternatingColorsTest,
    ::testing::ValuesIn(ShortestPathWithAlternatingColorsSolution().getStrategyNames()));

}  // namespace problem_1129
}  // namespace leetcode
