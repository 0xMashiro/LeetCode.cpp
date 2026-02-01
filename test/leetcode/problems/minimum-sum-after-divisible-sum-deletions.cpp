#include "leetcode/problems/minimum-sum-after-divisible-sum-deletions.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3654 {

class MinimumSumAfterDivisibleSumDeletionsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumSumAfterDivisibleSumDeletionsSolution solution;
};

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, Example1) {
  vector<int> nums = {1, 1, 1};
  int k = 2;
  long long expected = 1;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, Example2) {
  vector<int> nums = {3, 1, 4, 1, 5};
  int k = 3;
  long long expected = 5;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, SingleElementDivisible) {
  // 单个元素能被k整除，可以删除
  vector<int> nums = {5};
  int k = 5;
  long long expected = 0;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, SingleElementNotDivisible) {
  // 单个元素不能被k整除，无法删除
  vector<int> nums = {3};
  int k = 5;
  long long expected = 3;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, AllDivisible) {
  // 所有元素都能被k整除，可以全部删除
  vector<int> nums = {2, 4, 6, 8};
  int k = 2;
  long long expected = 0;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, NoneDivisible) {
  // 没有子数组和能被k整除，无法删除
  vector<int> nums = {1, 1, 1};
  int k = 10;
  long long expected = 3;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, LargeK) {
  // k 很大，无法删除
  vector<int> nums = {1, 2, 3};
  int k = 1000000;
  long long expected = 6;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, EntireArrayDivisible) {
  // 整个数组和能被k整除
  vector<int> nums = {1, 2, 3, 4};
  int k = 10;  // 1+2+3+4=10
  long long expected = 0;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, MultipleChoices) {
  // 多种删除选择，应该选择最优的
  // nums = [1, 2, 1], k = 2
  // 总和 = 4
  // 可以删除 [1,1] (位置0,2)，但不相邻，不能直接删除
  // 可以删除 [2]，剩余 [1,1]，和为2
  // 或者删除 [1,2,1]=4，但4%2==0，可以全部删除？不对，需要连续子数组
  // 实际上可以删除整个数组 [1,2,1]，和为4，4%2==0
  vector<int> nums = {1, 2, 1};
  int k = 2;
  long long expected = 0;  // 可以删除整个数组
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

TEST_P(MinimumSumAfterDivisibleSumDeletionsTest, ComplexCase) {
  // 更复杂的例子
  // nums = [2, 3, 2], k = 4
  // 总和 = 7
  // 可以删除 [2, 2] 吗？不相邻
  // 子数组和能被4整除的：[2,3,2]=7 不行，[2,3]=5 不行，[3,2]=5 不行
  // 单个元素：无
  // 所以无法删除，剩余7
  vector<int> nums = {2, 3, 2};
  int k = 4;
  long long expected = 7;
  EXPECT_EQ(expected, solution.minArraySum(nums, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumSumAfterDivisibleSumDeletionsTest,
    ::testing::ValuesIn(MinimumSumAfterDivisibleSumDeletionsSolution().getStrategyNames()));

}  // namespace problem_3654
}  // namespace leetcode
