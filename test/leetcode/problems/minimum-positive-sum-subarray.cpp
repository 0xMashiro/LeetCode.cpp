#include "leetcode/problems/minimum-positive-sum-subarray.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3364 {

class MinimumPositiveSumSubarrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumPositiveSumSubarraySolution solution;
};

// Example 1: nums = [3, -2, 1, 4], l = 2, r = 3, expected = 1
TEST_P(MinimumPositiveSumSubarrayTest, Example1) {
  vector<int> nums = {3, -2, 1, 4};
  int l = 2;
  int r = 3;
  int expected = 1;
  EXPECT_EQ(expected, solution.minimumSumSubarray(nums, l, r));
}

// Example 2: nums = [-2, 2, -3, 1], l = 2, r = 3, expected = -1
TEST_P(MinimumPositiveSumSubarrayTest, Example2) {
  vector<int> nums = {-2, 2, -3, 1};
  int l = 2;
  int r = 3;
  int expected = -1;
  EXPECT_EQ(expected, solution.minimumSumSubarray(nums, l, r));
}

// Example 3: nums = [1, 2, 3, 4], l = 2, r = 4, expected = 3
TEST_P(MinimumPositiveSumSubarrayTest, Example3) {
  vector<int> nums = {1, 2, 3, 4};
  int l = 2;
  int r = 4;
  int expected = 3;
  EXPECT_EQ(expected, solution.minimumSumSubarray(nums, l, r));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumPositiveSumSubarrayTest,
    ::testing::ValuesIn(MinimumPositiveSumSubarraySolution().getStrategyNames()));

}  // namespace problem_3364
}  // namespace leetcode
