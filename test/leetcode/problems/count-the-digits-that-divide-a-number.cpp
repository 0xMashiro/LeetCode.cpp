#include "leetcode/problems/count-the-digits-that-divide-a-number.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2520 {

class CountTheDigitsThatDivideANumberTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountTheDigitsThatDivideANumberSolution solution;
};

TEST_P(CountTheDigitsThatDivideANumberTest, Example1) {
  int num = 7;
  int expected = 1;
  EXPECT_EQ(expected, solution.countDigits(num));
}

TEST_P(CountTheDigitsThatDivideANumberTest, Example2) {
  int num = 121;
  int expected = 2;
  EXPECT_EQ(expected, solution.countDigits(num));
}

TEST_P(CountTheDigitsThatDivideANumberTest, Example3) {
  int num = 1248;
  int expected = 4;
  EXPECT_EQ(expected, solution.countDigits(num));
}

// 边界测试：包含数字 0 的情况（如 10, 20, 101 等）
TEST_P(CountTheDigitsThatDivideANumberTest, EdgeCaseWithZero) {
  // 10: 数字为 1 和 0，1 能整除 10，0 跳过
  EXPECT_EQ(1, solution.countDigits(10));
  // 20: 数字为 2 和 0，2 能整除 20，0 跳过
  EXPECT_EQ(1, solution.countDigits(20));
  // 101: 数字为 1, 0, 1，两个 1 都能整除 101
  EXPECT_EQ(2, solution.countDigits(101));
  // 100: 数字为 1, 0, 0，只有 1 能整除 100
  EXPECT_EQ(1, solution.countDigits(100));
}

// 边界测试：单个数字
TEST_P(CountTheDigitsThatDivideANumberTest, EdgeCaseSingleDigit) {
  // 1-9 都应该返回 1（单个数字总能整除自己）
  for (int i = 1; i <= 9; ++i) {
    EXPECT_EQ(1, solution.countDigits(i));
  }
}

// 边界测试：所有数字都能整除
TEST_P(CountTheDigitsThatDivideANumberTest, AllDigitsDivide) {
  // 111: 所有数字都是 1，都能整除 111
  EXPECT_EQ(3, solution.countDigits(111));
  // 222: 所有数字都是 2，都能整除 222
  EXPECT_EQ(3, solution.countDigits(222));
  // 36: 3 和 6 都能整除 36
  EXPECT_EQ(2, solution.countDigits(36));
}

// 边界测试：大数
TEST_P(CountTheDigitsThatDivideANumberTest, LargeNumber) {
  // 999999999: 所有数字都是 9，都能整除
  EXPECT_EQ(9, solution.countDigits(999999999));
  // 100000000: 只有 1 能整除
  EXPECT_EQ(1, solution.countDigits(100000000));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountTheDigitsThatDivideANumberTest,
    ::testing::ValuesIn(CountTheDigitsThatDivideANumberSolution().getStrategyNames()));

}  // namespace problem_2520
}  // namespace leetcode
