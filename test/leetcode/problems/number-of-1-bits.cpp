#include "leetcode/problems/number-of-1-bits.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_191 {

class NumberOf1BitsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOf1BitsSolution solution;
};

// 示例 1: n = 11 (二进制 1011) -> 3
TEST_P(NumberOf1BitsTest, Example1) {
  int n = 11;  // 1011
  EXPECT_EQ(3, solution.hammingWeight(n));
}

// 示例 2: n = 128 (二进制 10000000) -> 1
TEST_P(NumberOf1BitsTest, Example2) {
  int n = 128;  // 10000000
  EXPECT_EQ(1, solution.hammingWeight(n));
}

// 示例 3: n = 2147483645 -> 30
TEST_P(NumberOf1BitsTest, Example3) {
  int n = 2147483645;  // 1111111111111111111111111111101
  EXPECT_EQ(30, solution.hammingWeight(n));
}

// 边界：最小值 n = 1
TEST_P(NumberOf1BitsTest, SingleBit) {
  EXPECT_EQ(1, solution.hammingWeight(1));
}

// 边界：所有位都是 1 (n = 0x7FFFFFFF = 2147483647)
TEST_P(NumberOf1BitsTest, AllOnes) {
  int n = 2147483647;  // 31 个 1
  EXPECT_EQ(31, solution.hammingWeight(n));
}

// 边界：2 的幂次
TEST_P(NumberOf1BitsTest, PowersOfTwo) {
  for (int i = 0; i < 31; ++i) {
    EXPECT_EQ(1, solution.hammingWeight(1 << i));
  }
}

// 边界：连续多个 1
TEST_P(NumberOf1BitsTest, ConsecutiveOnes) {
  EXPECT_EQ(16, solution.hammingWeight(0xFFFF));      // 16 个 1 (低16位)
  EXPECT_EQ(8, solution.hammingWeight(0xFF));         // 8 个 1 (低8位)
  EXPECT_EQ(16, solution.hammingWeight(0x0F0F0F0F));  // 4个0x0F, 每个4个1, 共16个1
}

// 边界：n = 0 (虽然约束说 n >= 1，但测试一下)
TEST_P(NumberOf1BitsTest, Zero) {
  EXPECT_EQ(0, solution.hammingWeight(0));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOf1BitsTest,
    ::testing::ValuesIn(NumberOf1BitsSolution().getStrategyNames()));

}  // namespace problem_191
}  // namespace leetcode
