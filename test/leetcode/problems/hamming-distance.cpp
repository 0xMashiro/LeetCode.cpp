#include "leetcode/problems/hamming-distance.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_461 {

class HammingDistanceTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  HammingDistanceSolution solution;
};

// 示例1: x = 1, y = 4, 期望输出 2
// 1 = 0001, 4 = 0100, 有2位不同
TEST_P(HammingDistanceTest, Example1) {
  int x = 1;
  int y = 4;
  int expected = 2;
  EXPECT_EQ(expected, solution.hammingDistance(x, y));
}

// 示例2: x = 3, y = 1, 期望输出 1
// 3 = 0011, 1 = 0001, 有1位不同
TEST_P(HammingDistanceTest, Example2) {
  int x = 3;
  int y = 1;
  int expected = 1;
  EXPECT_EQ(expected, solution.hammingDistance(x, y));
}

// 边界: 两个相同的数，期望输出 0
TEST_P(HammingDistanceTest, SameNumbers) {
  int x = 7;
  int y = 7;
  int expected = 0;
  EXPECT_EQ(expected, solution.hammingDistance(x, y));
}

// 边界: 全0和全1 (32位)
// 0 = 0000...0000
// 0x7FFFFFFF = 0111...1111 (31个1, 因为约束是 2^31-1)
// 期望输出 31
TEST_P(HammingDistanceTest, ZeroAndMax) {
  int x = 0;
  int y = 0x7FFFFFFF;  // 2^31 - 1
  int expected = 31;
  EXPECT_EQ(expected, solution.hammingDistance(x, y));
}

// 边界: 两个都是0
TEST_P(HammingDistanceTest, BothZero) {
  int x = 0;
  int y = 0;
  int expected = 0;
  EXPECT_EQ(expected, solution.hammingDistance(x, y));
}

// 测试连续位不同的情况
TEST_P(HammingDistanceTest, AlternatingBits) {
  int x = 0b0101010101010101010101010101010;  // 0x2AAAAAAA
  int y = 0b1010101010101010101010101010101;  // 0x55555555
  int expected = 31;  // 除了最高位，其他都不同了
  EXPECT_EQ(expected, solution.hammingDistance(x, y));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, HammingDistanceTest,
    ::testing::ValuesIn(HammingDistanceSolution().getStrategyNames()));

}  // namespace problem_461
}  // namespace leetcode
