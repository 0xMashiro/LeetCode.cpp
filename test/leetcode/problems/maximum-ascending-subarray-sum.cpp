#include "leetcode/problems/maximum-ascending-subarray-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1800 {

class MaximumAscendingSubarraySumTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumAscendingSubarraySumSolution solution;
};

// 示例 1: [10,20,30,5,10,50] → 65 ([5,10,50])
TEST_P(MaximumAscendingSubarraySumTest, Example1) {
  vector<int> nums = {10, 20, 30, 5, 10, 50};
  EXPECT_EQ(65, solution.maxAscendingSum(nums));
}

// 示例 2: [10,20,30,40,50] → 150 (整个数组)
TEST_P(MaximumAscendingSubarraySumTest, Example2) {
  vector<int> nums = {10, 20, 30, 40, 50};
  EXPECT_EQ(150, solution.maxAscendingSum(nums));
}

// 示例 3: [12,17,15,13,10,11,12] → 33 ([10,11,12])
TEST_P(MaximumAscendingSubarraySumTest, Example3) {
  vector<int> nums = {12, 17, 15, 13, 10, 11, 12};
  EXPECT_EQ(33, solution.maxAscendingSum(nums));
}

// 边界：单元素
TEST_P(MaximumAscendingSubarraySumTest, SingleElement) {
  vector<int> nums = {100};
  EXPECT_EQ(100, solution.maxAscendingSum(nums));
}

// 边界：全部递减
TEST_P(MaximumAscendingSubarraySumTest, StrictlyDecreasing) {
  vector<int> nums = {50, 40, 30, 20, 10};
  EXPECT_EQ(50, solution.maxAscendingSum(nums));
}

// 边界：全部相等（非严格递增，每个元素单独算）
TEST_P(MaximumAscendingSubarraySumTest, AllEqual) {
  vector<int> nums = {5, 5, 5, 5, 5};
  EXPECT_EQ(5, solution.maxAscendingSum(nums));
}

// 边界：两个递增子数组，后面的和更大
TEST_P(MaximumAscendingSubarraySumTest, LaterSubarrayLarger) {
  vector<int> nums = {1, 2, 3, 1, 2, 3, 4, 5};
  // [1,2,3] sum=6, [1,2,3,4,5] sum=15
  EXPECT_EQ(15, solution.maxAscendingSum(nums));
}

// 边界：多个小递增段
TEST_P(MaximumAscendingSubarraySumTest, MultipleSmallSegments) {
  vector<int> nums = {3, 6, 10, 1, 2, 3, 4};
  // [3,6,10] sum=19, [1,2,3,4] sum=10
  EXPECT_EQ(19, solution.maxAscendingSum(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumAscendingSubarraySumTest,
    ::testing::ValuesIn(MaximumAscendingSubarraySumSolution().getStrategyNames()));

}  // namespace problem_1800
}  // namespace leetcode
