#include "leetcode/problems/total-waviness-of-numbers-in-range-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3753 {

class TotalWavinessOfNumbersInRangeIiTest
    : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TotalWavinessOfNumbersInRangeIiSolution solution;
};

// 官方示例 1
TEST_P(TotalWavinessOfNumbersInRangeIiTest, Example1) {
  long long num1 = 120;
  long long num2 = 130;
  long long expected = 3;
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

// 官方示例 2
TEST_P(TotalWavinessOfNumbersInRangeIiTest, Example2) {
  long long num1 = 198;
  long long num2 = 202;
  long long expected = 3;
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

// 官方示例 3
TEST_P(TotalWavinessOfNumbersInRangeIiTest, Example3) {
  long long num1 = 4848;
  long long num2 = 4848;
  long long expected = 2;
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

// 边界：范围只有一个数，且 < 3 位
TEST_P(TotalWavinessOfNumbersInRangeIiTest, SelfAuthoredSingleDigit) {
  long long num1 = 7;
  long long num2 = 7;
  long long expected = 0;
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

// 边界：范围只有一个数，2 位数
TEST_P(TotalWavinessOfNumbersInRangeIiTest, SelfAuthoredTwoDigit) {
  long long num1 = 42;
  long long num2 = 42;
  long long expected = 0;
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

// 边界：范围起始于 1
TEST_P(TotalWavinessOfNumbersInRangeIiTest, SelfAuthoredStartFromOne) {
  long long num1 = 1;
  long long num2 = 1;
  long long expected = 0;
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

// 自定义：三个连续数，其中一个有波状度
TEST_P(TotalWavinessOfNumbersInRangeIiTest, SelfAuthoredThreeConsecutive) {
  // 100: digits 1,0,0 -> 0 is not peak/valley (not strictly > both, not < both)
  // 101: digits 1,0,1 -> 0 is valley (1 > 0 < 1), waviness = 1
  // 102: digits 1,0,2 -> 0 is valley (1 > 0 < 2), waviness = 1
  // total = 2
  long long num1 = 100;
  long long num2 = 102;
  long long expected = 2;
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

// 全部是波峰：999 本身 waviness=0，但 989: 8 is peak
TEST_P(TotalWavinessOfNumbersInRangeIiTest, SelfAuthoredPeakOnly) {
  // 979: 7 is peak (9>7<9)... wait, 7 < 9 and 7 < 9, so 7 is valley
  // Let's do 989: 8 is peak (9<8>9)? No, 9>8 and 8<9, 8 is valley
  // Let's just test something simple: 818 -> 1 is valley (8>1<8)
  long long num1 = 818;
  long long num2 = 818;
  long long expected = 1;
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

// 大范围测试（只测 DigitDP，BruteForce 会超时跳过）
TEST_P(TotalWavinessOfNumbersInRangeIiTest, SelfAuthoredLargeRange) {
  long long num1 = 1;
  long long num2 = 1000;
  // 我们手动验证：小范围可以快速验证
  long long expected = 0;
  // 暴力验证 1~1000 的总波状度
  for (long long x = 1; x <= 1000; ++x) {
    std::string s = std::to_string(x);
    int n = (int)s.size();
    if (n < 3) continue;
    for (int i = 1; i < n - 1; ++i) {
      int l = s[i-1] - '0';
      int m = s[i] - '0';
      int r = s[i+1] - '0';
      if ((m > l && m > r) || (m < l && m < r)) ++expected;
    }
  }
  EXPECT_EQ(expected, solution.totalWaviness(num1, num2));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TotalWavinessOfNumbersInRangeIiTest,
    ::testing::ValuesIn(TotalWavinessOfNumbersInRangeIiSolution().getStrategyNames()));

}  // namespace problem_3753
}  // namespace leetcode
