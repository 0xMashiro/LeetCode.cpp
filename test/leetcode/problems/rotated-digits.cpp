#include "leetcode/problems/rotated-digits.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_788 {

class RotatedDigitsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RotatedDigitsSolution solution;
};

TEST_P(RotatedDigitsTest, Example1) {
  EXPECT_EQ(4, solution.rotatedDigits(10));
}

TEST_P(RotatedDigitsTest, Example2) {
  EXPECT_EQ(0, solution.rotatedDigits(1));
}

TEST_P(RotatedDigitsTest, Example3) {
  EXPECT_EQ(1, solution.rotatedDigits(2));
}

TEST_P(RotatedDigitsTest, SelfAuthoredSmall) {
  // 手动验证小范围 n 的累计好数个数
  // 好数：2,5,6,9
  EXPECT_EQ(0, solution.rotatedDigits(1));   // [1,1] 无好数
  EXPECT_EQ(1, solution.rotatedDigits(2));   // [1,2] -> {2}
  EXPECT_EQ(1, solution.rotatedDigits(3));   // [1,3] -> {2} (3无效)
  EXPECT_EQ(1, solution.rotatedDigits(4));   // [1,4] -> {2} (4无效)
  EXPECT_EQ(2, solution.rotatedDigits(5));   // [1,5] -> {2,5}
  EXPECT_EQ(3, solution.rotatedDigits(6));   // [1,6] -> {2,5,6}
  EXPECT_EQ(3, solution.rotatedDigits(7));   // [1,7] -> {2,5,6}
  EXPECT_EQ(3, solution.rotatedDigits(8));   // [1,8] -> {2,5,6} (8不变)
  EXPECT_EQ(4, solution.rotatedDigits(9));   // [1,9] -> {2,5,6,9}
  EXPECT_EQ(4, solution.rotatedDigits(10));  // [1,10] -> {2,5,6,9} (10不变)
}

TEST_P(RotatedDigitsTest, SelfAuthoredVerify30) {
  // n=30 时好数：2,5,6,9,12,15,16,19,20,21,22,25,26,28,29 共15个
  EXPECT_EQ(15, solution.rotatedDigits(30));
}

TEST_P(RotatedDigitsTest, SelfAuthoredEdge) {
  // 最大值测试 (n=10000)
  int result = solution.rotatedDigits(10000);
  EXPECT_GT(result, 0);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RotatedDigitsTest,
    ::testing::ValuesIn(RotatedDigitsSolution().getStrategyNames()));

}  // namespace problem_788
}  // namespace leetcode
