
#include "leetcode/problems/convert-a-number-to-hexadecimal.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_405 {

class ConvertANumberToHexadecimalTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConvertANumberToHexadecimalSolution solution;
};

TEST_P(ConvertANumberToHexadecimalTest, Example1) {
  int num = 26;
  string expected = "1a";
  EXPECT_EQ(expected, solution.toHex(num));
}

TEST_P(ConvertANumberToHexadecimalTest, Example2) {
  int num = -1;
  string expected = "ffffffff";
  EXPECT_EQ(expected, solution.toHex(num));
}

TEST_P(ConvertANumberToHexadecimalTest, Zero) {
  int num = 0;
  string expected = "0";
  EXPECT_EQ(expected, solution.toHex(num));
}

TEST_P(ConvertANumberToHexadecimalTest, PositiveSmall) {
  int num = 10;
  string expected = "a";
  EXPECT_EQ(expected, solution.toHex(num));
}

TEST_P(ConvertANumberToHexadecimalTest, NegativeSmall) {
  int num = -2;
  // -2 的补码：0xFFFFFFFE
  string expected = "fffffffe";
  EXPECT_EQ(expected, solution.toHex(num));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConvertANumberToHexadecimalTest,
    ::testing::ValuesIn(ConvertANumberToHexadecimalSolution().getStrategyNames()));

}  // namespace problem_405
}  // namespace leetcode
