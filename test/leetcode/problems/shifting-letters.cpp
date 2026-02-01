#include "leetcode/problems/shifting-letters.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_848 {

class ShiftingLettersTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ShiftingLettersSolution solution;
};

TEST_P(ShiftingLettersTest, Example1) {
  string s = "abc";
  vector<int> shifts = {3, 5, 9};
  string expected = "rpl";
  EXPECT_EQ(expected, solution.shiftingLetters(s, shifts));
}

TEST_P(ShiftingLettersTest, Example2) {
  string s = "aaa";
  vector<int> shifts = {1, 2, 3};
  string expected = "gfd";
  EXPECT_EQ(expected, solution.shiftingLetters(s, shifts));
}

TEST_P(ShiftingLettersTest, SingleChar) {
  string s = "z";
  vector<int> shifts = {1};
  string expected = "a";
  EXPECT_EQ(expected, solution.shiftingLetters(s, shifts));
}

TEST_P(ShiftingLettersTest, LargeShifts) {
  string s = "a";
  vector<int> shifts = {26};
  string expected = "a";  // 移动 26 位回到原位
  EXPECT_EQ(expected, solution.shiftingLetters(s, shifts));
}

TEST_P(ShiftingLettersTest, ZeroShifts) {
  string s = "abc";
  vector<int> shifts = {0, 0, 0};
  string expected = "abc";
  EXPECT_EQ(expected, solution.shiftingLetters(s, shifts));
}

TEST_P(ShiftingLettersTest, LargeShiftsMultiple) {
  string s = "abc";
  vector<int> shifts = {1000000000, 1000000000, 1000000000};
  // 10^9 % 26 = 1000000000 % 26 = 12
  // a + (12 + 12 + 12) % 26 = a + 10 = k
  // b + (12 + 12) % 26 = b + 24 = z
  // c + 12 % 26 = c + 12 = o
  string expected = "kzo";
  EXPECT_EQ(expected, solution.shiftingLetters(s, shifts));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ShiftingLettersTest,
    ::testing::ValuesIn(ShiftingLettersSolution().getStrategyNames()));

}  // namespace problem_848
}  // namespace leetcode
