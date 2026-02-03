#include "leetcode/problems/count-pairs-of-nodes.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1782 {

class CountPairsOfNodesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountPairsOfNodesSolution solution;
};

TEST_P(CountPairsOfNodesTest, Example1) {
  int n = 4;
  vector<vector<int>> edges = {{1, 2}, {2, 4}, {1, 3}, {2, 3}, {2, 1}};
  vector<int> queries = {2, 3};
  vector<int> expected = {6, 5};
  EXPECT_EQ(expected, solution.countPairs(n, edges, queries));
}

TEST_P(CountPairsOfNodesTest, Example2) {
  int n = 5;
  vector<vector<int>> edges = {{1, 5}, {1, 5}, {3, 4}, {2, 5}, {1, 3}, {5, 1}, {2, 3}, {2, 5}};
  vector<int> queries = {1, 2, 3, 4, 5};
  vector<int> expected = {10, 10, 9, 8, 6};
  EXPECT_EQ(expected, solution.countPairs(n, edges, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountPairsOfNodesTest,
    ::testing::ValuesIn(CountPairsOfNodesSolution().getStrategyNames()));

}  // namespace problem_1782
}  // namespace leetcode
