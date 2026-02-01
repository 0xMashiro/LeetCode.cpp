#include "leetcode/problems/binary-number-with-alternating-bits.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_693 {

class BinaryNumberWithAlternatingBitsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BinaryNumberWithAlternatingBitsSolution solution;
};

TEST_P(BinaryNumberWithAlternatingBitsTest, Example1) {
  // n = 5, binary: 101, alternating
  EXPECT_TRUE(solution.hasAlternatingBits(5));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, Example2) {
  // n = 7, binary: 111, not alternating
  EXPECT_FALSE(solution.hasAlternatingBits(7));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, Example3) {
  // n = 11, binary: 1011, not alternating (last two bits are 11)
  EXPECT_FALSE(solution.hasAlternatingBits(11));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, SingleBit) {
  // n = 1, binary: 1, single bit is always alternating
  EXPECT_TRUE(solution.hasAlternatingBits(1));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, TwoBitsAlternating) {
  // n = 2, binary: 10, alternating
  EXPECT_TRUE(solution.hasAlternatingBits(2));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, TwoBitsSame) {
  // n = 3, binary: 11, not alternating
  EXPECT_FALSE(solution.hasAlternatingBits(3));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, LongAlternatingPattern1) {
  // n = 10, binary: 1010, alternating
  EXPECT_TRUE(solution.hasAlternatingBits(10));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, LongAlternatingPattern2) {
  // n = 21, binary: 10101, alternating
  EXPECT_TRUE(solution.hasAlternatingBits(21));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, MaxAlternatingNumber) {
  // n = 1431655765 (0x55555555), binary: 01010101010101010101010101010101
  // This is the maximum alternating bit pattern for 32-bit integers
  EXPECT_TRUE(solution.hasAlternatingBits(1431655765));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, LargeNumberNotAlternating) {
  // n = 1431655766 (0x55555556), binary: 01010101010101010101010101010110
  // Last two bits are 10, but previous bits break the pattern at the end
  EXPECT_FALSE(solution.hasAlternatingBits(1431655766));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, PowerOfTwoNotAlternating) {
  // n = 8, binary: 1000, not alternating (has consecutive 0s)
  EXPECT_FALSE(solution.hasAlternatingBits(8));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, NearPowerOfTwoNotAlternating) {
  // n = 9, binary: 1001, not alternating (has consecutive 0s)
  EXPECT_FALSE(solution.hasAlternatingBits(9));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, AlternatingStartWithZero) {
  // n = 42, binary: 101010, alternating
  EXPECT_TRUE(solution.hasAlternatingBits(42));
}

TEST_P(BinaryNumberWithAlternatingBitsTest, FourConsecutiveSameBits) {
  // n = 15, binary: 1111, not alternating
  EXPECT_FALSE(solution.hasAlternatingBits(15));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BinaryNumberWithAlternatingBitsTest,
    ::testing::ValuesIn(BinaryNumberWithAlternatingBitsSolution().getStrategyNames()));

}  // namespace problem_693
}  // namespace leetcode
