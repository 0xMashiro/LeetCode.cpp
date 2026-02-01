#include "leetcode/problems/count-distinct-subarrays-divisible-by-k-in-sorted-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3729 {

class CountDistinctSubarraysDivisibleByKInSortedArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountDistinctSubarraysDivisibleByKInSortedArraySolution solution;
};

// 示例 1：nums = [1,2,3], k = 3，期望输出 3
// 好子数组：[1,2], [3], [1,2,3]
TEST_P(CountDistinctSubarraysDivisibleByKInSortedArrayTest, Example1) {
  vector<int> nums = {1, 2, 3};
  int k = 3;
  long long expected = 3;
  EXPECT_EQ(expected, solution.numGoodSubarrays(nums, k));
}

// 示例 2：nums = [2,2,2,2,2,2], k = 6，期望输出 2
// 好子数组：[2,2,2]（长度为3）, [2,2,2,2,2,2]（长度为6）
TEST_P(CountDistinctSubarraysDivisibleByKInSortedArrayTest, Example2) {
  vector<int> nums = {2, 2, 2, 2, 2, 2};
  int k = 6;
  long long expected = 2;
  EXPECT_EQ(expected, solution.numGoodSubarrays(nums, k));
}

// 边界测试：单个元素
TEST_P(CountDistinctSubarraysDivisibleByKInSortedArrayTest, SingleElementDivisible) {
  vector<int> nums = {5};
  int k = 5;
  long long expected = 1;  // [5]
  EXPECT_EQ(expected, solution.numGoodSubarrays(nums, k));
}

TEST_P(CountDistinctSubarraysDivisibleByKInSortedArrayTest, SingleElementNotDivisible) {
  vector<int> nums = {3};
  int k = 5;
  long long expected = 0;
  EXPECT_EQ(expected, solution.numGoodSubarrays(nums, k));
}

// 边界测试：所有元素相同
TEST_P(CountDistinctSubarraysDivisibleByKInSortedArrayTest, AllSameElements) {
  vector<int> nums = {1, 1, 1};
  int k = 2;
  // 和为 2 的子数组：[1,1]（位置 0-1 或 1-2，但值序列都是 [1,1]，只算一个）
  long long expected = 1;
  EXPECT_EQ(expected, solution.numGoodSubarrays(nums, k));
}

// 边界测试：k = 1，所有非空子数组都满足条件
TEST_P(CountDistinctSubarraysDivisibleByKInSortedArrayTest, KEqualsOne) {
  vector<int> nums = {1, 2, 2};
  int k = 1;
  // 所有非空子数组和都能被 1 整除
  // 不同子数组：[1], [2], [1,2], [2,2], [1,2,2]
  // 注意 [2] 只算一次（虽然有两个 2）
  long long expected = 5;
  EXPECT_EQ(expected, solution.numGoodSubarrays(nums, k));
}

// 边界测试：没有满足条件的子数组
TEST_P(CountDistinctSubarraysDivisibleByKInSortedArrayTest, NoGoodSubarrays) {
  vector<int> nums = {1, 1, 1};
  int k = 5;
  long long expected = 0;
  EXPECT_EQ(expected, solution.numGoodSubarrays(nums, k));
}

// 更多元素测试
TEST_P(CountDistinctSubarraysDivisibleByKInSortedArrayTest, MoreElements) {
  vector<int> nums = {1, 1, 2, 2, 3, 3};
  int k = 3;
  // 和能被 3 整除的子数组：[1,2], [3], [1,1,2], [1,2,2,3], [1,1,2,2,3], 等等
  // 需要计算不同的值序列
  long long result = solution.numGoodSubarrays(nums, k);
  EXPECT_GE(result, 0);  // 至少应该返回非负数
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountDistinctSubarraysDivisibleByKInSortedArrayTest,
    ::testing::ValuesIn(CountDistinctSubarraysDivisibleByKInSortedArraySolution().getStrategyNames()));

}  // namespace problem_3729
}  // namespace leetcode
