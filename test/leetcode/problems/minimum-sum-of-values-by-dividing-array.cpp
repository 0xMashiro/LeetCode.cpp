#include "leetcode/problems/minimum-sum-of-values-by-dividing-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3117 {

class MinimumSumOfValuesByDividingArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumSumOfValuesByDividingArraySolution solution;
};

// Example 1: nums = [1,4,3,3,2], andValues = [0,3,3,2] -> 12
// [1,4] AND=0, value=4; [3] AND=3, value=3; [3] AND=3, value=3; [2] AND=2, value=2
// Sum = 4+3+3+2 = 12
TEST_P(MinimumSumOfValuesByDividingArrayTest, Example1) {
  vector<int> nums = {1, 4, 3, 3, 2};
  vector<int> andValues = {0, 3, 3, 2};
  EXPECT_EQ(12, solution.minimumValueSum(nums, andValues));
}

// Example 2: nums = [2,3,5,7,7,7,5], andValues = [0,7,5] -> 17
// Best: [[2,3,5],[7,7,7],[5]] -> 5 + 7 + 5 = 17
TEST_P(MinimumSumOfValuesByDividingArrayTest, Example2) {
  vector<int> nums = {2, 3, 5, 7, 7, 7, 5};
  vector<int> andValues = {0, 7, 5};
  EXPECT_EQ(17, solution.minimumValueSum(nums, andValues));
}

// Example 3: nums = [1,2,3,4], andValues = [2] -> -1
// Entire array AND = 0, not 2
TEST_P(MinimumSumOfValuesByDividingArrayTest, Example3) {
  vector<int> nums = {1, 2, 3, 4};
  vector<int> andValues = {2};
  EXPECT_EQ(-1, solution.minimumValueSum(nums, andValues));
}

// Edge case: single element match
TEST_P(MinimumSumOfValuesByDividingArrayTest, SingleElementMatch) {
  vector<int> nums = {5};
  vector<int> andValues = {5};
  EXPECT_EQ(5, solution.minimumValueSum(nums, andValues));
}

// Edge case: single element no match
TEST_P(MinimumSumOfValuesByDividingArrayTest, SingleElementNoMatch) {
  vector<int> nums = {5};
  vector<int> andValues = {3};
  EXPECT_EQ(-1, solution.minimumValueSum(nums, andValues));
}

// Edge case: m > n (impossible)
TEST_P(MinimumSumOfValuesByDividingArrayTest, MoreSubarraysThanElements) {
  vector<int> nums = {1, 2};
  vector<int> andValues = {1, 2, 3};
  EXPECT_EQ(-1, solution.minimumValueSum(nums, andValues));
}

// Edge case: two elements, single subarray with AND
TEST_P(MinimumSumOfValuesByDividingArrayTest, TwoElementsSingleSubarray) {
  vector<int> nums = {3, 5};  // 3 & 5 = 1
  vector<int> andValues = {1};
  EXPECT_EQ(5, solution.minimumValueSum(nums, andValues));
}

// Edge case: all same elements
TEST_P(MinimumSumOfValuesByDividingArrayTest, AllSameElements) {
  vector<int> nums = {7, 7, 7, 7};
  vector<int> andValues = {7, 7};
  // [7] + [7,7,7] -> 7 + 7 = 14
  // [7,7] + [7,7] -> 7 + 7 = 14
  EXPECT_EQ(14, solution.minimumValueSum(nums, andValues));
}

// Test with zeros in nums
// nums = [0, 1, 2, 3], andValues = [0, 2]
// Must cover entire array: possible partitions are:
// [0,1,2,3] -> AND=0 (doesn't match [0,2])
// [0,1,2] + [3] -> AND=0, AND=3 (doesn't match)
// [0,1] + [2,3] -> AND=0, AND=2 -> MATCH! Sum = 1 + 3 = 4
TEST_P(MinimumSumOfValuesByDividingArrayTest, WithZeros) {
  vector<int> nums = {0, 1, 2, 3};
  vector<int> andValues = {0, 2};
  EXPECT_EQ(4, solution.minimumValueSum(nums, andValues));
}

// Test case: consecutive AND zeros
TEST_P(MinimumSumOfValuesByDividingArrayTest, MultipleZeroOptions) {
  vector<int> nums = {0, 0, 1};
  vector<int> andValues = {0, 0};
  // [0] + [0,1] -> 0 + 1 = 1
  // [0,0] + [1] -> 0 + 1 = 1
  EXPECT_EQ(1, solution.minimumValueSum(nums, andValues));
}

// Test case: larger numbers
TEST_P(MinimumSumOfValuesByDividingArrayTest, LargerNumbers) {
  vector<int> nums = {15, 15, 7, 7, 3};
  vector<int> andValues = {15, 7, 3};
  // [15] AND=15, value=15
  // [15,7,7] AND=7 (15&7=7, 7&7=7), value=7
  // [3] AND=3, value=3
  // Sum = 15 + 7 + 3 = 25
  EXPECT_EQ(25, solution.minimumValueSum(nums, andValues));
}

// Additional test: minimum values
TEST_P(MinimumSumOfValuesByDividingArrayTest, MinimumValues) {
  vector<int> nums = {1, 1};
  vector<int> andValues = {1, 1};
  // [1] + [1] -> 1 + 1 = 2
  EXPECT_EQ(2, solution.minimumValueSum(nums, andValues));
}

// Test: all elements must be used
TEST_P(MinimumSumOfValuesByDividingArrayTest, AllElementsMustBeUsed) {
  vector<int> nums = {1, 2, 3};
  vector<int> andValues = {1, 2};
  // [1] AND=1, [2,3] AND=2&3=2 -> MATCH! Sum = 1 + 3 = 4
  EXPECT_EQ(4, solution.minimumValueSum(nums, andValues));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumSumOfValuesByDividingArrayTest,
    ::testing::ValuesIn(MinimumSumOfValuesByDividingArraySolution().getStrategyNames()));

}  // namespace problem_3117
}  // namespace leetcode
