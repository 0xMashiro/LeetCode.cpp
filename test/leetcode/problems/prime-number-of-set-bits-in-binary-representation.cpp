
#include "leetcode/problems/prime-number-of-set-bits-in-binary-representation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_762 {

class PrimeNumberOfSetBitsInBinaryRepresentationTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PrimeNumberOfSetBitsInBinaryRepresentationSolution solution;
};

TEST_P(PrimeNumberOfSetBitsInBinaryRepresentationTest, Example1) {
  int left = 6;
  int right = 10;
  int expected = 4;
  EXPECT_EQ(expected, solution.countPrimeSetBits(left, right));
}

TEST_P(PrimeNumberOfSetBitsInBinaryRepresentationTest, Example2) {
  int left = 10;
  int right = 15;
  int expected = 5;
  EXPECT_EQ(expected, solution.countPrimeSetBits(left, right));
}

TEST_P(PrimeNumberOfSetBitsInBinaryRepresentationTest, SingleNumber) {
  int left = 7;
  int right = 7;
  // 7 -> 111, 3 set bits, 3 is prime
  int expected = 1;
  EXPECT_EQ(expected, solution.countPrimeSetBits(left, right));
}

TEST_P(PrimeNumberOfSetBitsInBinaryRepresentationTest, RangeWithNoPrimeSetBits) {
  int left = 1;
  int right = 1;
  // 1 -> 1, 1 set bit, 1 is not prime
  int expected = 0;
  EXPECT_EQ(expected, solution.countPrimeSetBits(left, right));
}

TEST_P(PrimeNumberOfSetBitsInBinaryRepresentationTest, PowerOfTwo) {
  int left = 1;
  int right = 8;
  // 1 -> 1 (not prime)
  // 2 -> 10 (1, not prime)
  // 3 -> 11 (2, prime)
  // 4 -> 100 (1, not prime)
  // 5 -> 101 (2, prime)
  // 6 -> 110 (2, prime)
  // 7 -> 111 (3, prime)
  // 8 -> 1000 (1, not prime)
  int expected = 4;
  EXPECT_EQ(expected, solution.countPrimeSetBits(left, right));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PrimeNumberOfSetBitsInBinaryRepresentationTest,
    ::testing::ValuesIn(PrimeNumberOfSetBitsInBinaryRepresentationSolution().getStrategyNames()));

}  // namespace problem_762
}  // namespace leetcode
