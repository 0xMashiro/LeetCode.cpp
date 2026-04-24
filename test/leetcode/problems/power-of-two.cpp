#include "leetcode/problems/power-of-two.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_231 {

class PowerOfTwoTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PowerOfTwoSolution solution;
};

TEST_P(PowerOfTwoTest, Example1) {
  // n = 1, 输出: true
  EXPECT_TRUE(solution.isPowerOfTwo(1));
}

TEST_P(PowerOfTwoTest, Example2) {
  // n = 16, 输出: true
  EXPECT_TRUE(solution.isPowerOfTwo(16));
}

TEST_P(PowerOfTwoTest, Example3) {
  // n = 3, 输出: false
  EXPECT_FALSE(solution.isPowerOfTwo(3));
}

TEST_P(PowerOfTwoTest, NegativeNumber) {
  // n = -16, 输出: false（负数不是2的幂）
  EXPECT_FALSE(solution.isPowerOfTwo(-16));
}

TEST_P(PowerOfTwoTest, Zero) {
  // n = 0, 输出: false
  EXPECT_FALSE(solution.isPowerOfTwo(0));
}

TEST_P(PowerOfTwoTest, OneIsPowerOfTwo) {
  // n = 1 (2^0), 输出: true
  EXPECT_TRUE(solution.isPowerOfTwo(1));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PowerOfTwoTest,
    ::testing::ValuesIn(PowerOfTwoSolution().getStrategyNames()));

}  // namespace problem_231
}  // namespace leetcode
