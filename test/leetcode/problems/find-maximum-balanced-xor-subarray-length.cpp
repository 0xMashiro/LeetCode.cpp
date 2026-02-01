#include "leetcode/problems/find-maximum-balanced-xor-subarray-length.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3755 {

class FindMaximumBalancedXorSubarrayLengthTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindMaximumBalancedXorSubarrayLengthSolution solution;
};

// Example 1: [3,1,3,2,0] -> 4
// Subarray [1, 3, 2, 0]: XOR = 1^3^2^0 = 0, 2 even + 2 odd
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, Example1) {
  vector<int> nums = {3, 1, 3, 2, 0};
  EXPECT_EQ(4, solution.maxBalancedSubarray(nums));
}

// Example 2: [3,2,8,5,4,14,9,15] -> 8
// Whole array: XOR = 0, 4 even + 4 odd
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, Example2) {
  vector<int> nums = {3, 2, 8, 5, 4, 14, 9, 15};
  EXPECT_EQ(8, solution.maxBalancedSubarray(nums));
}

// Example 3: [0] -> 0
// Single element 0: 0 is even, no valid subarray
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, Example3) {
  vector<int> nums = {0};
  EXPECT_EQ(0, solution.maxBalancedSubarray(nums));
}

// Additional test: empty result case
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, NoValidSubarray) {
  vector<int> nums = {1, 2, 3};
  // Need to check if there's any valid subarray
  EXPECT_EQ(0, solution.maxBalancedSubarray(nums));
}

// Additional test: simple valid case
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, SimpleValidCase) {
  vector<int> nums = {1, 1};  // XOR = 0, 0 even + 2 odd -> not valid
  // Actually this is not valid: 0 even, 2 odd
  // Let's find a valid one
  vector<int> nums2 = {2, 1, 3, 0};  // 2^1^3^0 = 0, 2 even + 2 odd
  EXPECT_EQ(4, solution.maxBalancedSubarray(nums2));
}

// Test with two elements: one even, one odd, XOR = 0
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, TwoElementValid) {
  // Need XOR = 0 and equal count
  // XOR = 0 means a ^ b = 0 => a = b
  // If a = b, then both even or both odd, count not equal
  // So no valid 2-element subarray of form [a, a]
  vector<int> nums = {5, 5};  // both odd
  EXPECT_EQ(0, solution.maxBalancedSubarray(nums));
}

// Test with all zeros (all even)
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, AllZeros) {
  vector<int> nums = {0, 0, 0, 0};
  // All even, XOR = 0, but can't have equal odd/even
  EXPECT_EQ(0, solution.maxBalancedSubarray(nums));
}

// Test with alternating pattern
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, AlternatingPattern) {
  // Create a case where XOR = 0 and equal count
  // [1, 2, 3]: 1^2^3 = 0, 1 even + 2 odd -> not valid
  // [1, 2, 3, 0]: 1^2^3^0 = 0, 2 even + 2 odd -> valid
  vector<int> nums = {1, 2, 3, 0};
  EXPECT_EQ(4, solution.maxBalancedSubarray(nums));
}

// Test with single even number
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, SingleEven) {
  vector<int> nums = {2};
  EXPECT_EQ(0, solution.maxBalancedSubarray(nums));
}

// Test with single odd number
TEST_P(FindMaximumBalancedXorSubarrayLengthTest, SingleOdd) {
  vector<int> nums = {1};
  EXPECT_EQ(0, solution.maxBalancedSubarray(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindMaximumBalancedXorSubarrayLengthTest,
    ::testing::ValuesIn(FindMaximumBalancedXorSubarrayLengthSolution().getStrategyNames()));

}  // namespace problem_3755
}  // namespace leetcode
