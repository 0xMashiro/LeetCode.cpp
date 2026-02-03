#include "leetcode/problems/partition-array-according-to-given-pivot.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2161 {

class PartitionArrayAccordingToGivenPivotTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PartitionArrayAccordingToGivenPivotSolution solution;
};

TEST_P(PartitionArrayAccordingToGivenPivotTest, Example1) {
  vector<int> nums = {9, 12, 5, 10, 14, 3, 10};
  int pivot = 10;
  vector<int> expected = {9, 5, 3, 10, 10, 12, 14};
  vector<int> result = solution.pivotArray(nums, pivot);
  EXPECT_EQ(expected, result);
}

TEST_P(PartitionArrayAccordingToGivenPivotTest, Example2) {
  vector<int> nums = {-3, 4, 3, 2};
  int pivot = 2;
  vector<int> expected = {-3, 2, 4, 3};
  vector<int> result = solution.pivotArray(nums, pivot);
  EXPECT_EQ(expected, result);
}

TEST_P(PartitionArrayAccordingToGivenPivotTest, AllLessThanPivot) {
  vector<int> nums = {1, 2, 3};
  int pivot = 5;
  vector<int> expected = {1, 2, 3};
  vector<int> result = solution.pivotArray(nums, pivot);
  EXPECT_EQ(expected, result);
}

TEST_P(PartitionArrayAccordingToGivenPivotTest, AllGreaterThanPivot) {
  vector<int> nums = {6, 7, 8};
  int pivot = 5;
  vector<int> expected = {6, 7, 8};
  vector<int> result = solution.pivotArray(nums, pivot);
  EXPECT_EQ(expected, result);
}

TEST_P(PartitionArrayAccordingToGivenPivotTest, AllEqualToPivot) {
  vector<int> nums = {5, 5, 5};
  int pivot = 5;
  vector<int> expected = {5, 5, 5};
  vector<int> result = solution.pivotArray(nums, pivot);
  EXPECT_EQ(expected, result);
}

TEST_P(PartitionArrayAccordingToGivenPivotTest, SingleElement) {
  vector<int> nums = {10};
  int pivot = 10;
  vector<int> expected = {10};
  vector<int> result = solution.pivotArray(nums, pivot);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PartitionArrayAccordingToGivenPivotTest,
    ::testing::ValuesIn(PartitionArrayAccordingToGivenPivotSolution().getStrategyNames()));

}  // namespace problem_2161
}  // namespace leetcode
