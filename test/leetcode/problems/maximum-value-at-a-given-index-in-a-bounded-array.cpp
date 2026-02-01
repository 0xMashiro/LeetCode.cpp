
#include "leetcode/problems/maximum-value-at-a-given-index-in-a-bounded-array.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1802 {

class MaximumValueAtAGivenIndexInABoundedArrayTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumValueAtAGivenIndexInABoundedArraySolution solution;
};

TEST_P(MaximumValueAtAGivenIndexInABoundedArrayTest, Example1) {
  int n = 4, index = 2, maxSum = 6;
  int expected = 2;
  EXPECT_EQ(expected, solution.maxValue(n, index, maxSum));
}

TEST_P(MaximumValueAtAGivenIndexInABoundedArrayTest, Example2) {
  int n = 6, index = 1, maxSum = 10;
  int expected = 3;
  EXPECT_EQ(expected, solution.maxValue(n, index, maxSum));
}

TEST_P(MaximumValueAtAGivenIndexInABoundedArrayTest, SingleElement) {
  // n = 1 的边界情况
  int n = 1, index = 0, maxSum = 5;
  int expected = 5;
  EXPECT_EQ(expected, solution.maxValue(n, index, maxSum));
}

TEST_P(MaximumValueAtAGivenIndexInABoundedArrayTest, IndexAtStart) {
  // index = 0 的边界情况
  int n = 5, index = 0, maxSum = 10;
  // 左边长度 0，右边长度 4
  // mid=3: 3 + calculateSideSum(2, 4) = 3 + (2+1+1+1) = 3+5 = 8 <= 10
  // mid=4: 4 + calculateSideSum(3, 4) = 4 + (3+2+1+1) = 4+7 = 11 > 10
  int expected = 3;
  EXPECT_EQ(expected, solution.maxValue(n, index, maxSum));
}

TEST_P(MaximumValueAtAGivenIndexInABoundedArrayTest, IndexAtEnd) {
  // index = n-1 的边界情况
  int n = 5, index = 4, maxSum = 10;
  // 左边长度 4，右边长度 0
  // mid=2: 2 + calculateSideSum(1, 4) = 2 + (1+1+1+1) = 2+4 = 6 <= 10
  // mid=3: 3 + calculateSideSum(2, 4) = 3 + (2+1+1+1) = 3+5 = 8 <= 10
  // mid=4: 4 + calculateSideSum(3, 4) = 4 + (3+2+1+1) = 4+7 = 11 > 10
  int expected = 3;
  EXPECT_EQ(expected, solution.maxValue(n, index, maxSum));
}

TEST_P(MaximumValueAtAGivenIndexInABoundedArrayTest, LargeValue) {
  // 大数值测试
  int n = 3, index = 2, maxSum = 18;
  // 左边长度 2，右边长度 0
  // mid=7: 7 + calculateSideSum(6, 2) = 7 + (6+5) = 7+11 = 18 <= 18
  // mid=8: 8 + calculateSideSum(7, 2) = 8 + (7+6) = 8+13 = 21 > 18
  int expected = 7;
  EXPECT_EQ(expected, solution.maxValue(n, index, maxSum));
}

TEST_P(MaximumValueAtAGivenIndexInABoundedArrayTest, AllOnes) {
  // 当 maxSum 刚好等于 n 时，所有元素都必须是 1
  int n = 5, index = 2, maxSum = 5;
  int expected = 1;
  EXPECT_EQ(expected, solution.maxValue(n, index, maxSum));
}

TEST_P(MaximumValueAtAGivenIndexInABoundedArrayTest, SymmetricCase) {
  // 对称情况，index 在中间
  int n = 5, index = 2, maxSum = 9;
  // 期望数组：[1,2,3,2,1]，和 = 9
  int expected = 3;
  EXPECT_EQ(expected, solution.maxValue(n, index, maxSum));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumValueAtAGivenIndexInABoundedArrayTest,
    ::testing::ValuesIn(MaximumValueAtAGivenIndexInABoundedArraySolution().getStrategyNames()));

}  // namespace problem_1802
}  // namespace leetcode
