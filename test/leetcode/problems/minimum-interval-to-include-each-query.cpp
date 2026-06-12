#include "leetcode/problems/minimum-interval-to-include-each-query.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1851 {

class MinimumIntervalToIncludeEachQueryTest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumIntervalToIncludeEachQuerySolution solution;
};

TEST_P(MinimumIntervalToIncludeEachQueryTest, Example1) {
  vector<vector<int>> intervals = {{1, 4}, {2, 4}, {3, 6}, {4, 4}};
  vector<int> queries = {2, 3, 4, 5};
  vector<int> expected = {3, 3, 1, 4};
  EXPECT_EQ(expected, solution.minInterval(intervals, queries));
}

TEST_P(MinimumIntervalToIncludeEachQueryTest, Example2) {
  vector<vector<int>> intervals = {{2, 3}, {2, 5}, {1, 8}, {20, 25}};
  vector<int> queries = {2, 19, 5, 22};
  vector<int> expected = {2, -1, 4, 6};
  EXPECT_EQ(expected, solution.minInterval(intervals, queries));
}

TEST_P(MinimumIntervalToIncludeEachQueryTest,
       SelfAuthoredSingleIntervalSingleQuery) {
  vector<vector<int>> intervals = {{5, 10}};
  vector<int> queries = {7};
  vector<int> expected = {6};  // 10 - 5 + 1 = 6
  EXPECT_EQ(expected, solution.minInterval(intervals, queries));
}

TEST_P(MinimumIntervalToIncludeEachQueryTest, SelfAuthoredNoIntervalCovers) {
  vector<vector<int>> intervals = {{1, 2}, {4, 5}};
  vector<int> queries = {3};
  vector<int> expected = {-1};
  EXPECT_EQ(expected, solution.minInterval(intervals, queries));
}

TEST_P(MinimumIntervalToIncludeEachQueryTest, SelfAuthoredSameSizeIntervals) {
  vector<vector<int>> intervals = {{1, 5}, {6, 10}};
  vector<int> queries = {3, 8};
  vector<int> expected = {5, 5};  // both have size 5
  EXPECT_EQ(expected, solution.minInterval(intervals, queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumIntervalToIncludeEachQueryTest,
    ::testing::ValuesIn(
        MinimumIntervalToIncludeEachQuerySolution().getStrategyNames()));

}  // namespace problem_1851
}  // namespace leetcode
