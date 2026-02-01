
#include "leetcode/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3430 {

class MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumAndMinimumSumsOfAtMostSizeKSubarraysSolution solution;
};

TEST_P(MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest, Example1) {
  vector<int> nums = {1, 2, 3};
  int k = 2;
  long long expected = 20;
  EXPECT_EQ(expected, solution.minMaxSubarraySum(nums, k));
}

TEST_P(MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest, Example2) {
  vector<int> nums = {1, -3, 1};
  int k = 2;
  long long expected = -6;
  EXPECT_EQ(expected, solution.minMaxSubarraySum(nums, k));
}

TEST_P(MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest, SingleElement) {
  vector<int> nums = {5};
  int k = 1;
  // 只有一个子数组 [5]，min=5, max=5, sum=10
  long long expected = 10;
  EXPECT_EQ(expected, solution.minMaxSubarraySum(nums, k));
}

TEST_P(MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest, AllSameElements) {
  vector<int> nums = {2, 2, 2};
  int k = 2;
  // 子数组: [2], [2], [2], [2,2], [2,2]
  // 每个子数组 min=max=2, sum=4
  // 共5个子数组，总和=20
  long long expected = 20;
  EXPECT_EQ(expected, solution.minMaxSubarraySum(nums, k));
}

TEST_P(MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest, KEqualToN) {
  vector<int> nums = {1, 2, 3};
  int k = 3;
  // 子数组: [1], [2], [3], [1,2], [2,3], [1,2,3]
  // [1]: 1+1=2, [2]: 2+2=4, [3]: 3+3=6
  // [1,2]: 1+2=3, [2,3]: 2+3=5, [1,2,3]: 1+3=4
  // 总和 = 2+4+6+3+5+4 = 24
  long long expected = 24;
  EXPECT_EQ(expected, solution.minMaxSubarraySum(nums, k));
}

TEST_P(MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest, NegativeNumbers) {
  vector<int> nums = {-1, -2, -3};
  int k = 2;
  // 子数组: [-1], [-2], [-3], [-1,-2], [-2,-3]
  // [-1]: -1+-1=-2, [-2]: -2+-2=-4, [-3]: -3+-3=-6
  // [-1,-2]: min=-2, max=-1, sum=-3
  // [-2,-3]: min=-3, max=-2, sum=-5
  // 总和 = -2-4-6-3-5 = -20
  long long expected = -20;
  EXPECT_EQ(expected, solution.minMaxSubarraySum(nums, k));
}

TEST_P(MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest, MixedNumbers) {
  vector<int> nums = {1, -1, 1};
  int k = 2;
  // 子数组: [1], [-1], [1], [1,-1], [-1,1]
  // [1]: 2, [-1]: -2, [1]: 2
  // [1,-1]: min=-1, max=1, sum=0
  // [-1,1]: min=-1, max=1, sum=0
  // 总和 = 2-2+2+0+0 = 2
  long long expected = 2;
  EXPECT_EQ(expected, solution.minMaxSubarraySum(nums, k));
}

TEST_P(MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest, LargeK) {
  vector<int> nums = {1, 2};
  int k = 5;  // k > n
  // 子数组: [1], [2], [1,2]
  // [1]: 2, [2]: 4, [1,2]: 1+2=3
  // 总和 = 9
  long long expected = 9;
  EXPECT_EQ(expected, solution.minMaxSubarraySum(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumAndMinimumSumsOfAtMostSizeKSubarraysTest,
    ::testing::ValuesIn(MaximumAndMinimumSumsOfAtMostSizeKSubarraysSolution().getStrategyNames()));

}  // namespace problem_3430
}  // namespace leetcode
