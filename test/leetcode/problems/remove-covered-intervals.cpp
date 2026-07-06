#include "leetcode/problems/remove-covered-intervals.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1288 {

class RemoveCoveredIntervalsTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RemoveCoveredIntervalsSolution solution;
};

TEST_P(RemoveCoveredIntervalsTest, Example1) {
  std::vector<std::vector<int>> intervals = {{1, 4}, {3, 6}, {2, 8}};
  int expected = 2;
  EXPECT_EQ(expected, solution.removeCoveredIntervals(intervals));
}

TEST_P(RemoveCoveredIntervalsTest, Example2) {
  std::vector<std::vector<int>> intervals = {{1, 4}, {2, 3}};
  int expected = 1;
  EXPECT_EQ(expected, solution.removeCoveredIntervals(intervals));
}

TEST_P(RemoveCoveredIntervalsTest, SelfAuthoredNoOverlap) {
  std::vector<std::vector<int>> intervals = {{1, 2}, {3, 4}, {5, 6}};
  int expected = 3;
  EXPECT_EQ(expected, solution.removeCoveredIntervals(intervals));
}

TEST_P(RemoveCoveredIntervalsTest, SelfAuthoredNestedAll) {
  std::vector<std::vector<int>> intervals = {{1, 10}, {2, 9}, {3, 8}, {4, 7}};
  int expected = 1;
  EXPECT_EQ(expected, solution.removeCoveredIntervals(intervals));
}

TEST_P(RemoveCoveredIntervalsTest, SelfAuthoredSameLeftDifferentRight) {
  std::vector<std::vector<int>> intervals = {{1, 4}, {1, 5}};
  int expected = 1;  // [1,4] 被 [1,5] 覆盖
  EXPECT_EQ(expected, solution.removeCoveredIntervals(intervals));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RemoveCoveredIntervalsTest,
    ::testing::ValuesIn(RemoveCoveredIntervalsSolution().getStrategyNames()));

}  // namespace problem_1288
}  // namespace leetcode
