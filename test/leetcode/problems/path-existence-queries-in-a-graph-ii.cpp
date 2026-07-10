#include "leetcode/problems/path-existence-queries-in-a-graph-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3534 {

class PathExistenceQueriesInAGraphIiTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PathExistenceQueriesInAGraphIiSolution solution;
};

TEST_P(PathExistenceQueriesInAGraphIiTest, Example1) {
  int n = 5;
  std::vector<int> nums = {1, 8, 3, 4, 2};
  int maxDiff = 3;
  std::vector<std::vector<int>> queries = {{0, 3}, {2, 4}};
  std::vector<int> expected = {1, 1};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphIiTest, Example2) {
  int n = 5;
  std::vector<int> nums = {5, 3, 1, 9, 10};
  int maxDiff = 2;
  std::vector<std::vector<int>> queries = {{0, 1}, {0, 2}, {2, 3}, {4, 3}};
  std::vector<int> expected = {1, 2, -1, 1};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphIiTest, Example3) {
  int n = 3;
  std::vector<int> nums = {3, 6, 1};
  int maxDiff = 1;
  std::vector<std::vector<int>> queries = {{0, 0}, {0, 1}, {1, 2}};
  std::vector<int> expected = {0, -1, -1};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphIiTest, SelfAuthoredSelfLoop) {
  int n = 4;
  std::vector<int> nums = {10, 20, 30, 40};
  int maxDiff = 5;
  std::vector<std::vector<int>> queries = {{1, 1}, {3, 3}};
  std::vector<int> expected = {0, 0};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphIiTest, SelfAuthoredSingleChain) {
  // 所有相邻差值 <= maxDiff，整个数组连通
  int n = 6;
  std::vector<int> nums = {1, 3, 5, 7, 9, 11};
  int maxDiff = 2;
  std::vector<std::vector<int>> queries = {{0, 5}, {0, 3}, {2, 4}};
  std::vector<int> expected = {5, 3, 2};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphIiTest, SelfAuthoredDisconnected) {
  int n = 5;
  std::vector<int> nums = {1, 2, 10, 11, 20};
  int maxDiff = 3;
  std::vector<std::vector<int>> queries = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
  std::vector<int> expected = {1, -1, 1, -1};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PathExistenceQueriesInAGraphIiTest,
    ::testing::ValuesIn(
        PathExistenceQueriesInAGraphIiSolution().getStrategyNames()));

}  // namespace problem_3534
}  // namespace leetcode
