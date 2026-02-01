#include "leetcode/problems/divide-two-integers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_29 {

class DivideTwoIntegersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DivideTwoIntegersSolution solution;
};

// 示例 1: dividend = 10, divisor = 3，结果 = 3
TEST_P(DivideTwoIntegersTest, Example1) {
  EXPECT_EQ(3, solution.divide(10, 3));
}

// 示例 2: dividend = 7, divisor = -3，结果 = -2
TEST_P(DivideTwoIntegersTest, Example2) {
  EXPECT_EQ(-2, solution.divide(7, -3));
}

// 边界情况：被除数为 0
TEST_P(DivideTwoIntegersTest, DividendIsZero) {
  EXPECT_EQ(0, solution.divide(0, 1));
  EXPECT_EQ(0, solution.divide(0, -1));
}

// 边界情况：除数为 1 或 -1
TEST_P(DivideTwoIntegersTest, DivisorIsOneOrNegativeOne) {
  EXPECT_EQ(100, solution.divide(100, 1));
  EXPECT_EQ(-100, solution.divide(100, -1));
  EXPECT_EQ(-100, solution.divide(-100, 1));
  EXPECT_EQ(100, solution.divide(-100, -1));
}

// 边界情况：被除数等于除数
TEST_P(DivideTwoIntegersTest, DividendEqualsDivisor) {
  EXPECT_EQ(1, solution.divide(5, 5));
  EXPECT_EQ(1, solution.divide(-5, -5));
  EXPECT_EQ(-1, solution.divide(5, -5));
  EXPECT_EQ(-1, solution.divide(-5, 5));
}

// 边界情况：被除数为 INT_MIN，除数为 -1（溢出情况）
TEST_P(DivideTwoIntegersTest, OverflowCase) {
  EXPECT_EQ(INT_MAX, solution.divide(INT_MIN, -1));
}

// 边界情况：被除数为 INT_MIN，除数为 1
TEST_P(DivideTwoIntegersTest, IntMinDividedByOne) {
  EXPECT_EQ(INT_MIN, solution.divide(INT_MIN, 1));
}

// 边界情况：除数为 INT_MIN
TEST_P(DivideTwoIntegersTest, DivisorIsIntMin) {
  EXPECT_EQ(0, solution.divide(INT_MAX, INT_MIN));
  EXPECT_EQ(1, solution.divide(INT_MIN, INT_MIN));
}

// 边界情况：大数相除
TEST_P(DivideTwoIntegersTest, LargeNumbers) {
  EXPECT_EQ(INT_MAX / 2, solution.divide(INT_MAX, 2));
  EXPECT_EQ(INT_MIN / 2, solution.divide(INT_MIN, 2));
}

// 边界情况：结果为 1
TEST_P(DivideTwoIntegersTest, ResultIsOne) {
  EXPECT_EQ(1, solution.divide(INT_MAX, INT_MAX));
  EXPECT_EQ(1, solution.divide(INT_MIN + 1, INT_MIN + 1));
}

// 边界情况：结果为 -1
TEST_P(DivideTwoIntegersTest, ResultIsNegativeOne) {
  EXPECT_EQ(-1, solution.divide(INT_MAX, INT_MIN + 1));
  EXPECT_EQ(-1, solution.divide(INT_MIN + 1, INT_MAX));
}

// 边界情况：结果为 0（被除数绝对值小于除数绝对值）
TEST_P(DivideTwoIntegersTest, ResultIsZero) {
  EXPECT_EQ(0, solution.divide(1, 2));
  EXPECT_EQ(0, solution.divide(-1, 2));
  EXPECT_EQ(0, solution.divide(1, -2));
  EXPECT_EQ(0, solution.divide(-1, -2));
}

// 特殊情况：INT_MIN / 2
TEST_P(DivideTwoIntegersTest, IntMinDividedByTwo) {
  EXPECT_EQ(INT_MIN / 2, solution.divide(INT_MIN, 2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DivideTwoIntegersTest,
    ::testing::ValuesIn(DivideTwoIntegersSolution().getStrategyNames()));

}  // namespace problem_29
}  // namespace leetcode
