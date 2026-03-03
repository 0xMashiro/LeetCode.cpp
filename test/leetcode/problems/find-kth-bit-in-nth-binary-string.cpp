#include "leetcode/problems/find-kth-bit-in-nth-binary-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1545 {

class FindKthBitInNthBinaryStringTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindKthBitInNthBinaryStringSolution solution;
};

TEST_P(FindKthBitInNthBinaryStringTest, Example1) {
  // n = 3, k = 1, S₃ = "0111001", 第1位是 "0"
  EXPECT_EQ('0', solution.findKthBit(3, 1));
}

TEST_P(FindKthBitInNthBinaryStringTest, Example2) {
  // n = 4, k = 11, S₄ = "011100110110001", 第11位是 "1"
  EXPECT_EQ('1', solution.findKthBit(4, 11));
}

TEST_P(FindKthBitInNthBinaryStringTest, MiddlePosition) {
  // 测试中间位置，应该是 "1"
  // S₂ = "011", 中间位置 k = 2
  EXPECT_EQ('1', solution.findKthBit(2, 2));
  // S₃ = "0111001", 中间位置 k = 4
  EXPECT_EQ('1', solution.findKthBit(3, 4));
}

TEST_P(FindKthBitInNthBinaryStringTest, LastPosition) {
  // 测试最后一个位置
  // S₂ = "011", 最后一位 k = 3 是 "1"
  EXPECT_EQ('1', solution.findKthBit(2, 3));
  // S₃ = "0111001", 最后一位 k = 7 是 "1"
  EXPECT_EQ('1', solution.findKthBit(3, 7));
}

TEST_P(FindKthBitInNthBinaryStringTest, FirstPosition) {
  // S₁ = "0", 第一位 k = 1 是 "0"
  EXPECT_EQ('0', solution.findKthBit(1, 1));
  // Sₙ 的第一位总是 "0"
  EXPECT_EQ('0', solution.findKthBit(5, 1));
  EXPECT_EQ('0', solution.findKthBit(10, 1));
}

TEST_P(FindKthBitInNthBinaryStringTest, SmallCases) {
  // S₂ = "011"
  EXPECT_EQ('0', solution.findKthBit(2, 1));
  EXPECT_EQ('1', solution.findKthBit(2, 2));
  EXPECT_EQ('1', solution.findKthBit(2, 3));
  
  // S₃ = "0111001"
  EXPECT_EQ('0', solution.findKthBit(3, 1));
  EXPECT_EQ('1', solution.findKthBit(3, 2));
  EXPECT_EQ('1', solution.findKthBit(3, 3));
  EXPECT_EQ('1', solution.findKthBit(3, 4));
  EXPECT_EQ('0', solution.findKthBit(3, 5));
  EXPECT_EQ('0', solution.findKthBit(3, 6));
  EXPECT_EQ('1', solution.findKthBit(3, 7));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindKthBitInNthBinaryStringTest,
    ::testing::ValuesIn(FindKthBitInNthBinaryStringSolution().getStrategyNames()));

}  // namespace problem_1545
}  // namespace leetcode
