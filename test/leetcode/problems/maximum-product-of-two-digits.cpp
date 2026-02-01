#include "leetcode/problems/maximum-product-of-two-digits.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3536 {

class MaximumProductOfTwoDigitsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumProductOfTwoDigitsSolution solution;
};

// Example 1: n = 31, digits = [3, 1], max product = 3
TEST_P(MaximumProductOfTwoDigitsTest, Example1) {
  int n = 31;
  int expected = 3;
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// Example 2: n = 22, digits = [2, 2], max product = 4
TEST_P(MaximumProductOfTwoDigitsTest, Example2) {
  int n = 22;
  int expected = 4;
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// Example 3: n = 124, digits = [1, 2, 4], max product = 8
TEST_P(MaximumProductOfTwoDigitsTest, Example3) {
  int n = 124;
  int expected = 8;
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// 边界：两位数，最小值 n = 10
TEST_P(MaximumProductOfTwoDigitsTest, MinimumTwoDigits) {
  int n = 10;
  int expected = 0;  // 1 * 0 = 0
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// 边界：两位数，最大值 n = 99
TEST_P(MaximumProductOfTwoDigitsTest, MaxTwoDigits) {
  int n = 99;
  int expected = 81;  // 9 * 9 = 81
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// 边界：多位数，包含 0
TEST_P(MaximumProductOfTwoDigitsTest, ContainsZero) {
  int n = 105;
  int expected = 5;  // 1 * 5 = 5
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// 边界：多位数，所有数字相同
TEST_P(MaximumProductOfTwoDigitsTest, AllSameDigits) {
  int n = 7777;
  int expected = 49;  // 7 * 7 = 49
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// 边界：大数，987654321 只有一个 9，最大乘积 = 9 * 8 = 72
TEST_P(MaximumProductOfTwoDigitsTest, LargeNumber) {
  int n = 987654321;
  int expected = 72;  // 9 * 8 = 72
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// 边界：包含重复的最大数字
TEST_P(MaximumProductOfTwoDigitsTest, DuplicateMaxDigits) {
  int n = 99123;
  int expected = 81;  // 9 * 9 = 81
  EXPECT_EQ(expected, solution.maxProduct(n));
}

// 边界：递增序列
TEST_P(MaximumProductOfTwoDigitsTest, AscendingDigits) {
  int n = 123456789;
  int expected = 72;  // 9 * 8 = 72
  EXPECT_EQ(expected, solution.maxProduct(n));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumProductOfTwoDigitsTest,
    ::testing::ValuesIn(MaximumProductOfTwoDigitsSolution().getStrategyNames()));

}  // namespace problem_3536
}  // namespace leetcode
