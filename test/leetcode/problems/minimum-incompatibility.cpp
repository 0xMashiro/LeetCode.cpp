
#include "leetcode/problems/minimum-incompatibility.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1681 {

class MinimumIncompatibilityTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumIncompatibilitySolution solution;
};

// Example 1: nums = [1,2,1,4], k = 2, output = 4
TEST_P(MinimumIncompatibilityTest, Example1) {
  vector<int> nums = {1, 2, 1, 4};
  int k = 2;
  int expected = 4;
  EXPECT_EQ(expected, solution.minimumIncompatibility(nums, k));
}

// Example 2: nums = [6,3,8,1,3,1,2,2], k = 4, output = 6
TEST_P(MinimumIncompatibilityTest, Example2) {
  vector<int> nums = {6, 3, 8, 1, 3, 1, 2, 2};
  int k = 4;
  int expected = 6;
  EXPECT_EQ(expected, solution.minimumIncompatibility(nums, k));
}

// Example 3: nums = [5,3,3,6,3,3], k = 3, output = -1 (impossible)
TEST_P(MinimumIncompatibilityTest, Example3) {
  vector<int> nums = {5, 3, 3, 6, 3, 3};
  int k = 3;
  int expected = -1;
  EXPECT_EQ(expected, solution.minimumIncompatibility(nums, k));
}

// Boundary: single element per subset
TEST_P(MinimumIncompatibilityTest, SingleElementPerSubset) {
  vector<int> nums = {1, 2, 3, 4};
  int k = 4;
  int expected = 0;  // Each subset has one element, incompatibility = 0
  EXPECT_EQ(expected, solution.minimumIncompatibility(nums, k));
}

// Boundary: k = 1, entire array is one subset
TEST_P(MinimumIncompatibilityTest, KEquals1) {
  vector<int> nums = {1, 2, 3, 4, 5};
  int k = 1;
  int expected = 4;  // max - min = 5 - 1 = 4
  EXPECT_EQ(expected, solution.minimumIncompatibility(nums, k));
}

// Boundary: duplicate elements that can be distributed
TEST_P(MinimumIncompatibilityTest, DistributableDuplicates) {
  vector<int> nums = {1, 1, 2, 2};
  int k = 2;
  int expected = 1;  // [1,2] and [1,2], incompatibility = (2-1) + (2-1) = 2
  // Actually: [1,2] and [1,2] -> (2-1) + (2-1) = 2
  // But wait, let me recalculate: min=1, max=2 for each, so 1+1=2
  expected = 2;
  EXPECT_EQ(expected, solution.minimumIncompatibility(nums, k));
}

// Boundary: all same elements, impossible
TEST_P(MinimumIncompatibilityTest, AllSameElements) {
  vector<int> nums = {1, 1, 1, 1};
  int k = 2;
  int expected = -1;  // Cannot distribute, each subset would have duplicates
  EXPECT_EQ(expected, solution.minimumIncompatibility(nums, k));
}

// Boundary: n = 16, max constraint
TEST_P(MinimumIncompatibilityTest, MaxConstraint) {
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  int k = 4;
  // Each subset has 4 elements, optimal is to group consecutive numbers
  // [1,2,3,4], [5,6,7,8], [9,10,11,12], [13,14,15,16]
  // Incompatibility: 3 + 3 + 3 + 3 = 12
  int expected = 12;
  EXPECT_EQ(expected, solution.minimumIncompatibility(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumIncompatibilityTest,
    ::testing::ValuesIn(MinimumIncompatibilitySolution().getStrategyNames()));

}  // namespace problem_1681
}  // namespace leetcode
