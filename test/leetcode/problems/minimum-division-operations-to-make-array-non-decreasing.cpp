#include "leetcode/problems/minimum-division-operations-to-make-array-non-decreasing.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3326 {

class MinimumDivisionOperationsToMakeArrayNonDecreasingTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumDivisionOperationsToMakeArrayNonDecreasingSolution solution;
};

// Example 1: nums = [25,7], Output: 1
// 25 除以最大真因数 5，变成 5，数组变为 [5, 7]
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, Example1) {
  vector<int> nums = {25, 7};
  EXPECT_EQ(1, solution.minOperations(nums));
}

// Example 2: nums = [7,7,6], Output: -1
// 无法使数组非递减
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, Example2) {
  vector<int> nums = {7, 7, 6};
  EXPECT_EQ(-1, solution.minOperations(nums));
}

// Example 3: nums = [1,1,1,1], Output: 0
// 已经非递减，不需要操作
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, Example3) {
  vector<int> nums = {1, 1, 1, 1};
  EXPECT_EQ(0, solution.minOperations(nums));
}

// 边界测试：空数组
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, EmptyArray) {
  vector<int> nums = {};
  EXPECT_EQ(0, solution.minOperations(nums));
}

// 边界测试：单元素数组
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, SingleElement) {
  vector<int> nums = {100};
  EXPECT_EQ(0, solution.minOperations(nums));
}

// 边界测试：两个相同元素
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, TwoSameElements) {
  vector<int> nums = {5, 5};
  EXPECT_EQ(0, solution.minOperations(nums));
}

// 边界测试：两个元素需要多次操作
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, TwoElementsMultipleOps) {
  // 100 -> 2 (最小质因数) -> 2 是质数，停止
  // 需要 1 次操作
  vector<int> nums = {100, 2};
  EXPECT_EQ(1, solution.minOperations(nums));
}

// 边界测试：复杂情况，需要多次操作
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, ComplexCase) {
  // 27 = 3^3，27 -> 3 -> 3 (质数)
  // 需要 1 次操作变成 3
  vector<int> nums = {27, 5};
  EXPECT_EQ(1, solution.minOperations(nums));
}

// 边界测试：质数无法减小
TEST_P(MinimumDivisionOperationsToMakeArrayNonDecreasingTest, PrimeCannotReduce) {
  // 7 是质数，无法减小，7 > 5，所以返回 -1
  vector<int> nums = {7, 5};
  EXPECT_EQ(-1, solution.minOperations(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumDivisionOperationsToMakeArrayNonDecreasingTest,
    ::testing::ValuesIn(MinimumDivisionOperationsToMakeArrayNonDecreasingSolution().getStrategyNames()));

}  // namespace problem_3326
}  // namespace leetcode
