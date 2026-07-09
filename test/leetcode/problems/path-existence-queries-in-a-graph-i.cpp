#include "leetcode/problems/path-existence-queries-in-a-graph-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3532 {

class PathExistenceQueriesInAGraphITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PathExistenceQueriesInAGraphISolution solution;
};

TEST_P(PathExistenceQueriesInAGraphITest, Example1) {
  int n = 2;
  std::vector<int> nums = {1, 3};
  int maxDiff = 1;
  std::vector<std::vector<int>> queries = {{0, 0}, {0, 1}};
  std::vector<bool> expected = {true, false};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphITest, Example2) {
  int n = 4;
  std::vector<int> nums = {2, 5, 6, 8};
  int maxDiff = 2;
  std::vector<std::vector<int>> queries = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
  std::vector<bool> expected = {false, false, true, true};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphITest, SelfAuthoredSingleNode) {
  int n = 1;
  std::vector<int> nums = {5};
  int maxDiff = 0;
  std::vector<std::vector<int>> queries = {{0, 0}};
  std::vector<bool> expected = {true};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphITest, SelfAuthoredAllConnected) {
  int n = 5;
  std::vector<int> nums = {1, 2, 3, 4, 5};
  int maxDiff = 1;
  std::vector<std::vector<int>> queries = {{0, 4}, {1, 3}, {0, 2}};
  std::vector<bool> expected = {true, true, true};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphITest, SelfAuthoredAllDisconnected) {
  int n = 3;
  std::vector<int> nums = {1, 10, 20};
  int maxDiff = 5;
  std::vector<std::vector<int>> queries = {{0, 1}, {1, 2}, {0, 2}};
  std::vector<bool> expected = {false, false, false};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

TEST_P(PathExistenceQueriesInAGraphITest, SelfAuthoredLargeGap) {
  // nums = [0, 2, 4, 100, 102, 104], maxDiff = 2
  // groups: {0,1,2} and {3,4,5}
  int n = 6;
  std::vector<int> nums = {0, 2, 4, 100, 102, 104};
  int maxDiff = 2;
  std::vector<std::vector<int>> queries = {{0, 2}, {0, 3}, {3, 5}, {1, 4}};
  std::vector<bool> expected = {true, false, true, false};
  EXPECT_EQ(expected, solution.pathExistenceQueries(n, nums, maxDiff, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PathExistenceQueriesInAGraphITest,
    ::testing::ValuesIn(PathExistenceQueriesInAGraphISolution().getStrategyNames()));

}  // namespace problem_3532
}  // namespace leetcode
