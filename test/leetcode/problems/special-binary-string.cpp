#include "leetcode/problems/special-binary-string.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_761 {

class SpecialBinaryStringTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SpecialBinaryStringSolution solution;
};

TEST_P(SpecialBinaryStringTest, Example1) {
  string s = "11011000";
  string expected = "11100100";
  EXPECT_EQ(expected, solution.makeLargestSpecial(s));
}

TEST_P(SpecialBinaryStringTest, Example2) {
  string s = "10";
  string expected = "10";
  EXPECT_EQ(expected, solution.makeLargestSpecial(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SpecialBinaryStringTest,
    ::testing::ValuesIn(SpecialBinaryStringSolution().getStrategyNames()));

}  // namespace problem_761
}  // namespace leetcode
