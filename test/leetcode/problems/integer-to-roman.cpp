#include "leetcode/problems/integer-to-roman.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_12 {

class IntegerToRomanTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  IntegerToRomanSolution solution;
};

TEST_P(IntegerToRomanTest, Example1) {
  int num = 3749;
  string expected = "MMMDCCXLIX";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, Example2) {
  int num = 58;
  string expected = "LVIII";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, Example3) {
  int num = 1994;
  string expected = "MCMXCIV";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, MinValue) {
  // 边界：最小值 1
  int num = 1;
  string expected = "I";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, MaxValue) {
  // 边界：最大值 3999
  int num = 3999;
  string expected = "MMMCMXCIX";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, SpecialCase4) {
  // 特殊情况：4 = IV
  int num = 4;
  string expected = "IV";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, SpecialCase9) {
  // 特殊情况：9 = IX
  int num = 9;
  string expected = "IX";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, SpecialCase40) {
  // 特殊情况：40 = XL
  int num = 40;
  string expected = "XL";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, SpecialCase90) {
  // 特殊情况：90 = XC
  int num = 90;
  string expected = "XC";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, SpecialCase400) {
  // 特殊情况：400 = CD
  int num = 400;
  string expected = "CD";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

TEST_P(IntegerToRomanTest, SpecialCase900) {
  // 特殊情况：900 = CM
  int num = 900;
  string expected = "CM";
  EXPECT_EQ(expected, solution.intToRoman(num));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, IntegerToRomanTest,
    ::testing::ValuesIn(IntegerToRomanSolution().getStrategyNames()));

}  // namespace problem_12
}  // namespace leetcode