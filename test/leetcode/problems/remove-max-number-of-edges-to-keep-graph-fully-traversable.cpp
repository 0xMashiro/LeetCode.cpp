#include "leetcode/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1579 {

class RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableSolution solution;
};

TEST_P(RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableTest, Example1) {
  int n = 4;
  vector<vector<int>> edges = {{3, 1, 2}, {3, 2, 3}, {1, 1, 3}, {1, 2, 4}, {1, 1, 2}, {2, 3, 4}};
  int expected = 2;
  EXPECT_EQ(expected, solution.maxNumEdgesToRemove(n, edges));
}

TEST_P(RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableTest, Example2) {
  int n = 4;
  vector<vector<int>> edges = {{3, 1, 2}, {3, 2, 3}, {1, 1, 4}, {2, 1, 4}};
  int expected = 0;
  EXPECT_EQ(expected, solution.maxNumEdgesToRemove(n, edges));
}

TEST_P(RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableTest, Example3) {
  int n = 4;
  vector<vector<int>> edges = {{3, 2, 3}, {1, 1, 2}, {2, 3, 4}};
  int expected = -1;
  EXPECT_EQ(expected, solution.maxNumEdgesToRemove(n, edges));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableTest,
    ::testing::ValuesIn(RemoveMaxNumberOfEdgesToKeepGraphFullyTraversableSolution().getStrategyNames()));

}  // namespace problem_1579
}  // namespace leetcode
