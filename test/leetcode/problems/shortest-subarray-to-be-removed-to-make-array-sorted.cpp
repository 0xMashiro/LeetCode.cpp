#include "leetcode/problems/shortest-subarray-to-be-removed-to-make-array-sorted.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1574 {

class ShortestSubarrayToBeRemovedToMakeArraySortedTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ShortestSubarrayToBeRemovedToMakeArraySortedSolution solution;
};

TEST_P(ShortestSubarrayToBeRemovedToMakeArraySortedTest, Example1) {
  vector<int> arr = {1, 2, 3, 10, 4, 2, 3, 5};
  int expected = 3;
  EXPECT_EQ(expected, solution.findLengthOfShortestSubarray(arr));
}

TEST_P(ShortestSubarrayToBeRemovedToMakeArraySortedTest, Example2) {
  vector<int> arr = {5, 4, 3, 2, 1};
  int expected = 4;
  EXPECT_EQ(expected, solution.findLengthOfShortestSubarray(arr));
}

TEST_P(ShortestSubarrayToBeRemovedToMakeArraySortedTest, Example3) {
  vector<int> arr = {1, 2, 3};
  int expected = 0;
  EXPECT_EQ(expected, solution.findLengthOfShortestSubarray(arr));
}

TEST_P(ShortestSubarrayToBeRemovedToMakeArraySortedTest, SingleElement) {
  vector<int> arr = {1};
  int expected = 0;
  EXPECT_EQ(expected, solution.findLengthOfShortestSubarray(arr));
}

TEST_P(ShortestSubarrayToBeRemovedToMakeArraySortedTest, TwoElementsSorted) {
  vector<int> arr = {1, 2};
  int expected = 0;
  EXPECT_EQ(expected, solution.findLengthOfShortestSubarray(arr));
}

TEST_P(ShortestSubarrayToBeRemovedToMakeArraySortedTest, TwoElementsUnsorted) {
  vector<int> arr = {2, 1};
  int expected = 1;
  EXPECT_EQ(expected, solution.findLengthOfShortestSubarray(arr));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ShortestSubarrayToBeRemovedToMakeArraySortedTest,
    ::testing::ValuesIn(ShortestSubarrayToBeRemovedToMakeArraySortedSolution().getStrategyNames()));

}  // namespace problem_1574
}  // namespace leetcode
