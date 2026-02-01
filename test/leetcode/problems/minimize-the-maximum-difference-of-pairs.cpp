
#include "leetcode/problems/minimize-the-maximum-difference-of-pairs.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2616 {

class MinimizeTheMaximumDifferenceOfPairsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimizeTheMaximumDifferenceOfPairsSolution solution;
};

// Example 1: nums = [10,1,2,7,1,3], p = 2, Output: 1
TEST_P(MinimizeTheMaximumDifferenceOfPairsTest, Example1) {
  vector<int> nums = {10, 1, 2, 7, 1, 3};
  int p = 2;
  int expected = 1;
  EXPECT_EQ(expected, solution.minimizeMax(nums, p));
}

// Example 2: nums = [4,2,1,2], p = 1, Output: 0
TEST_P(MinimizeTheMaximumDifferenceOfPairsTest, Example2) {
  vector<int> nums = {4, 2, 1, 2};
  int p = 1;
  int expected = 0;
  EXPECT_EQ(expected, solution.minimizeMax(nums, p));
}

// Edge case: p = 0, should return 0
TEST_P(MinimizeTheMaximumDifferenceOfPairsTest, PIsZero) {
  vector<int> nums = {1, 2, 3, 4, 5};
  int p = 0;
  int expected = 0;
  EXPECT_EQ(expected, solution.minimizeMax(nums, p));
}

// Edge case: single pair possible
TEST_P(MinimizeTheMaximumDifferenceOfPairsTest, SinglePair) {
  vector<int> nums = {5, 3};
  int p = 1;
  int expected = 2;
  EXPECT_EQ(expected, solution.minimizeMax(nums, p));
}

// Edge case: all elements same
TEST_P(MinimizeTheMaximumDifferenceOfPairsTest, AllSameElements) {
  vector<int> nums = {5, 5, 5, 5, 5, 5};
  int p = 3;
  int expected = 0;
  EXPECT_EQ(expected, solution.minimizeMax(nums, p));
}

// Edge case: strictly increasing
TEST_P(MinimizeTheMaximumDifferenceOfPairsTest, StrictlyIncreasing) {
  vector<int> nums = {1, 2, 3, 4, 5, 6};
  int p = 3;
  int expected = 1;  // pairs: (1,2), (3,4), (5,6), all diff = 1
  EXPECT_EQ(expected, solution.minimizeMax(nums, p));
}

// Edge case: large differences
TEST_P(MinimizeTheMaximumDifferenceOfPairsTest, LargeDifferences) {
  vector<int> nums = {1, 1000000000};
  int p = 1;
  int expected = 999999999;
  EXPECT_EQ(expected, solution.minimizeMax(nums, p));
}

// Additional test: need to skip some elements to get optimal result
TEST_P(MinimizeTheMaximumDifferenceOfPairsTest, SkipElements) {
  vector<int> nums = {1, 1, 2, 3, 7, 8};
  int p = 2;
  // Sorted: [1, 1, 2, 3, 7, 8]
  // Best pairs: (1,1) diff=0, (7,8) diff=1, max=1
  // Or: (1,2) diff=1, (7,8) diff=1, max=1
  int expected = 1;
  EXPECT_EQ(expected, solution.minimizeMax(nums, p));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimizeTheMaximumDifferenceOfPairsTest,
    ::testing::ValuesIn(MinimizeTheMaximumDifferenceOfPairsSolution().getStrategyNames()));

}  // namespace problem_2616
}  // namespace leetcode
