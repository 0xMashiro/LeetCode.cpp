#include "leetcode/problems/four-divisors.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1390 {

class FourDivisorsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FourDivisorsSolution solution;
};

TEST_P(FourDivisorsTest, Example1) {
  vector<int> nums = {21, 4, 7};
  int expected = 32;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

TEST_P(FourDivisorsTest, Example2) {
  vector<int> nums = {21, 21};
  int expected = 64;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

TEST_P(FourDivisorsTest, Example3) {
  vector<int> nums = {1, 2, 3, 4, 5};
  int expected = 0;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

TEST_P(FourDivisorsTest, SingleNumberWithFourDivisors) {
  vector<int> nums = {6};  // 6 = 2 * 3, divisors: 1,2,3,6, sum = 12
  int expected = 12;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

TEST_P(FourDivisorsTest, PrimeCube) {
  vector<int> nums = {8};  // 8 = 2^3, divisors: 1,2,4,8, sum = 15
  int expected = 15;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

TEST_P(FourDivisorsTest, MixedNumbers) {
  vector<int> nums = {6, 8, 10, 14, 15, 21, 22, 26, 27, 33};
  // 6: 1+2+3+6=12, 8:15, 10:1+2+5+10=18, 14:1+2+7+14=24, 15:1+3+5+15=24,
  // 21:1+3+7+21=32, 22:1+2+11+22=36, 26:1+2+13+26=42, 27:1+3+9+27=40,
  // 33:1+3+11+33=48
  // Only numbers with exactly 4 divisors: 6,8,10,14,15,21,22,26,33 (27 has 4 divisors? 27=3^3, divisors: 1,3,9,27 yes 4 divisors)
  // Actually 27 is prime cube, so has 4 divisors.
  // Let's compute sum: 12+15+18+24+24+32+36+42+40+48 = 291
  int expected = 12 + 15 + 18 + 24 + 24 + 32 + 36 + 42 + 40 + 48;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

TEST_P(FourDivisorsTest, LargeNumber) {
  vector<int> nums = {99991};  // 99991 is prime, only 2 divisors
  int expected = 0;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

TEST_P(FourDivisorsTest, NumberAtUpperBound) {
  vector<int> nums = {100000};  // 100000 = 2^5 * 5^5, divisor count > 4
  int expected = 0;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

TEST_P(FourDivisorsTest, EmptyArray) {
  vector<int> nums = {};
  int expected = 0;
  EXPECT_EQ(expected, solution.sumFourDivisors(nums));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FourDivisorsTest,
    ::testing::ValuesIn(FourDivisorsSolution().getStrategyNames()));

}  // namespace problem_1390
}  // namespace leetcode