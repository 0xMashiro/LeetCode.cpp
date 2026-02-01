#include "leetcode/problems/minimum-addition-to-make-integer-beautiful.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2457 {

class MinimumAdditionToMakeIntegerBeautifulTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumAdditionToMakeIntegerBeautifulSolution solution;
};

// 辅助函数：计算数字的各位之和
static long long digitSum(long long n) {
  long long sum = 0;
  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, Example1) {
  // n = 16, target = 6
  // 初始数字和: 1 + 6 = 7 > 6
  // 加 4 后: 20, 数字和: 2 + 0 = 2 <= 6
  long long n = 16;
  int target = 6;
  long long result = solution.makeIntegerBeautiful(n, target);
  EXPECT_EQ(result, 4);
  EXPECT_LE(digitSum(n + result), target);
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, Example2) {
  // n = 467, target = 6
  // 初始数字和: 4 + 6 + 7 = 17 > 6
  // 加 33 后: 500, 数字和: 5 + 0 + 0 = 5 <= 6
  long long n = 467;
  int target = 6;
  long long result = solution.makeIntegerBeautiful(n, target);
  EXPECT_EQ(result, 33);
  EXPECT_LE(digitSum(n + result), target);
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, Example3) {
  // n = 1, target = 1
  // 初始数字和: 1 <= 1，已经是美丽数
  long long n = 1;
  int target = 1;
  long long result = solution.makeIntegerBeautiful(n, target);
  EXPECT_EQ(result, 0);
  EXPECT_LE(digitSum(n + result), target);
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, AlreadyBeautiful) {
  // 已经是美丽数的情况
  long long n = 123;
  int target = 10;  // 1+2+3=6 <= 10
  long long result = solution.makeIntegerBeautiful(n, target);
  EXPECT_EQ(result, 0);
  EXPECT_LE(digitSum(n + result), target);
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, LargeNumber) {
  // 大数测试
  long long n = 999999999999LL;  // 12 个 9
  int target = 1;
  long long result = solution.makeIntegerBeautiful(n, target);
  EXPECT_LE(digitSum(n + result), target);
  // 结果应该是 1000000000000 - 999999999999 = 1
  EXPECT_EQ(result, 1);
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, SingleDigit) {
  // 单个数字，需要增加的情况
  long long n = 9;
  int target = 1;
  long long result = solution.makeIntegerBeautiful(n, target);
  EXPECT_EQ(result, 1);  // 9 + 1 = 10, 数字和 1
  EXPECT_LE(digitSum(n + result), target);
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, NeedMultipleCarry) {
  // 需要多次进位的情况
  long long n = 199;
  int target = 2;  // 1+9+9=19 > 2
  long long result = solution.makeIntegerBeautiful(n, target);
  // 199 -> 200, 加 1, 但 2+0+0=2 <= 2，满足条件
  EXPECT_EQ(result, 1);
  EXPECT_LE(digitSum(n + result), target);
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, PowerOfTen) {
  // 10 的幂次
  long long n = 1000;
  int target = 1;  // 1+0+0+0=1 <= 1
  long long result = solution.makeIntegerBeautiful(n, target);
  EXPECT_EQ(result, 0);
  EXPECT_LE(digitSum(n + result), target);
}

TEST_P(MinimumAdditionToMakeIntegerBeautifulTest, BoundaryValue) {
  // 边界值测试
  long long n = 1;
  int target = 150;  // 最大 target
  long long result = solution.makeIntegerBeautiful(n, target);
  EXPECT_EQ(result, 0);
  EXPECT_LE(digitSum(n + result), target);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumAdditionToMakeIntegerBeautifulTest,
    ::testing::ValuesIn(MinimumAdditionToMakeIntegerBeautifulSolution().getStrategyNames()));

}  // namespace problem_2457
}  // namespace leetcode
