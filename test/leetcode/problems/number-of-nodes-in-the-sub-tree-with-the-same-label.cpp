#include "leetcode/problems/number-of-nodes-in-the-sub-tree-with-the-same-label.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1519 {

class NumberOfNodesInTheSubTreeWithTheSameLabelTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfNodesInTheSubTreeWithTheSameLabelSolution solution;
};

TEST_P(NumberOfNodesInTheSubTreeWithTheSameLabelTest, Example1) {
  int n = 7;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}};
  string labels = "abaedcd";
  vector<int> expected = {2, 1, 1, 1, 1, 1, 1};
  vector<int> result = solution.countSubTrees(n, edges, labels);
  EXPECT_EQ(expected, result);
}

TEST_P(NumberOfNodesInTheSubTreeWithTheSameLabelTest, Example2) {
  int n = 4;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {0, 3}};
  string labels = "bbbb";
  vector<int> expected = {4, 2, 1, 1};
  vector<int> result = solution.countSubTrees(n, edges, labels);
  EXPECT_EQ(expected, result);
}

TEST_P(NumberOfNodesInTheSubTreeWithTheSameLabelTest, Example3) {
  int n = 5;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {0, 4}};
  string labels = "aabab";
  vector<int> expected = {3, 2, 1, 1, 1};
  vector<int> result = solution.countSubTrees(n, edges, labels);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfNodesInTheSubTreeWithTheSameLabelTest,
    ::testing::ValuesIn(NumberOfNodesInTheSubTreeWithTheSameLabelSolution().getStrategyNames()));

}  // namespace problem_1519
}  // namespace leetcode
