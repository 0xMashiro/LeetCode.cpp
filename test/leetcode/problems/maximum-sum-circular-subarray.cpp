#include "leetcode/problems/maximum-sum-circular-subarray.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_918 {

class MaximumSumCircularSubarrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumSumCircularSubarraySolution solution;
};

// 示例 1：普通情况，不跨越边界
TEST_P(MaximumSumCircularSubarrayTest, Example1) {
  vector<int> nums = {1, -2, 3, -2};
  EXPECT_EQ(3, solution.maxSubarraySumCircular(nums));
}

// 示例 2：环形情况，跨越边界
TEST_P(MaximumSumCircularSubarrayTest, Example2) {
  vector<int> nums = {5, -3, 5};
  EXPECT_EQ(10, solution.maxSubarraySumCircular(nums));
}

// 示例 3：全负数，选择最大（最小负数）
TEST_P(MaximumSumCircularSubarrayTest, Example3) {
  vector<int> nums = {-3, -2, -3};
  EXPECT_EQ(-2, solution.maxSubarraySumCircular(nums));
}

// 边界测试：单个元素
TEST_P(MaximumSumCircularSubarrayTest, SingleElement) {
  vector<int> nums = {5};
  EXPECT_EQ(5, solution.maxSubarraySumCircular(nums));
}

// 边界测试：单个负数
TEST_P(MaximumSumCircularSubarrayTest, SingleNegativeElement) {
  vector<int> nums = {-5};
  EXPECT_EQ(-5, solution.maxSubarraySumCircular(nums));
}

// 边界测试：两个元素
TEST_P(MaximumSumCircularSubarrayTest, TwoElements) {
  vector<int> nums = {1, 2};
  EXPECT_EQ(3, solution.maxSubarraySumCircular(nums));
}

// 边界测试：全正数，环形和 = 总和
TEST_P(MaximumSumCircularSubarrayTest, AllPositive) {
  vector<int> nums = {1, 2, 3, 4, 5};
  EXPECT_EQ(15, solution.maxSubarraySumCircular(nums));
}

// 边界测试：全零
TEST_P(MaximumSumCircularSubarrayTest, AllZeros) {
  vector<int> nums = {0, 0, 0};
  EXPECT_EQ(0, solution.maxSubarraySumCircular(nums));
}

// 特殊情况：正负交替
TEST_P(MaximumSumCircularSubarrayTest, AlternatingSigns) {
  vector<int> nums = {3, -1, 2, -1};
  // 最大和可以是 [3, -1, 2] = 4 或 [2, -1, 3] = 4 或 [3, -1, 2, -1] 跨越环形 = 3
  // 实际上最大是 3 - 1 + 2 - 1 + 3(环形) 不对，子数组只能包含每个元素最多一次
  // 正确：3 + (-1) + 2 = 4
  EXPECT_EQ(4, solution.maxSubarraySumCircular(nums));
}

// 测试跨越边界的环形子数组
TEST_P(MaximumSumCircularSubarrayTest, CrossBoundary) {
  vector<int> nums = {8, -4, 3, -5, 4};
  // 最大子数组是 [4, 8] 跨越边界 = 12
  EXPECT_EQ(12, solution.maxSubarraySumCircular(nums));
}

// 大规模测试（用于性能验证）
TEST_P(MaximumSumCircularSubarrayTest, LargeAllNegative) {
  vector<int> nums = {-30000, -20000, -10000};
  EXPECT_EQ(-10000, solution.maxSubarraySumCircular(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumSumCircularSubarrayTest,
    ::testing::ValuesIn(MaximumSumCircularSubarraySolution().getStrategyNames()));

}  // namespace problem_918
}  // namespace leetcode
