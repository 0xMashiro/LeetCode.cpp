#include "leetcode/problems/maximum-score-of-spliced-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2321 {

class MaximumScoreOfSplicedArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumScoreOfSplicedArraySolution solution;
};

// Example 1: 交换后 nums1 最大化
TEST_P(MaximumScoreOfSplicedArrayTest, Example1) {
  vector<int> nums1 = {60, 60, 60};
  vector<int> nums2 = {10, 90, 10};
  EXPECT_EQ(210, solution.maximumsSplicedArray(nums1, nums2));
}

// Example 2: 交换后 nums2 最大化
TEST_P(MaximumScoreOfSplicedArrayTest, Example2) {
  vector<int> nums1 = {20, 40, 20, 70, 30};
  vector<int> nums2 = {50, 20, 50, 40, 20};
  EXPECT_EQ(220, solution.maximumsSplicedArray(nums1, nums2));
}

// Example 3: 不交换是最优的
TEST_P(MaximumScoreOfSplicedArrayTest, Example3) {
  vector<int> nums1 = {7, 11, 13};
  vector<int> nums2 = {1, 1, 1};
  EXPECT_EQ(31, solution.maximumsSplicedArray(nums1, nums2));
}

// 边界情况：单元素数组
TEST_P(MaximumScoreOfSplicedArrayTest, SingleElement) {
  vector<int> nums1 = {100};
  vector<int> nums2 = {50};
  // max(100, 50) = 100，不交换
  EXPECT_EQ(100, solution.maximumsSplicedArray(nums1, nums2));
  
  vector<int> nums1b = {50};
  vector<int> nums2b = {100};
  // 交换后 nums1 = 100，分数 = 100
  EXPECT_EQ(100, solution.maximumsSplicedArray(nums1b, nums2b));
}

// 边界情况：两个数组相同
TEST_P(MaximumScoreOfSplicedArrayTest, SameArrays) {
  vector<int> nums1 = {10, 20, 30};
  vector<int> nums2 = {10, 20, 30};
  // 交换不改变任何东西，diff 全为 0
  EXPECT_EQ(60, solution.maximumsSplicedArray(nums1, nums2));
}

// 边界情况：需要交换整个数组
TEST_P(MaximumScoreOfSplicedArrayTest, SwapAll) {
  vector<int> nums1 = {1, 1, 1};
  vector<int> nums2 = {100, 100, 100};
  // 交换全部后 nums1 = 300
  EXPECT_EQ(300, solution.maximumsSplicedArray(nums1, nums2));
}

// 边界情况：负数 diff 但前面有正数铺垫
TEST_P(MaximumScoreOfSplicedArrayTest, MixedDiff) {
  vector<int> nums1 = {10, 20, 30, 40, 50};
  vector<int> nums2 = {10, 50, 20, 60, 10};
  // sum(nums1) = 150, sum(nums2) = 150
  // diff = [0, 30, -10, 20, -40]
  // max subarray of diff = 0+30-10+20 = 40 (left=0, right=3)
  // max subarray of -diff = 40 (from -40 at the end)
  // result = max(150+40, 150+40) = 190
  EXPECT_EQ(190, solution.maximumsSplicedArray(nums1, nums2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumScoreOfSplicedArrayTest,
    ::testing::ValuesIn(MaximumScoreOfSplicedArraySolution().getStrategyNames()));

}  // namespace problem_2321
}  // namespace leetcode
