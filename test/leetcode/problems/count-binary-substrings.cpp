
#include "leetcode/problems/count-binary-substrings.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_696 {

class CountBinarySubstringsTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountBinarySubstringsSolution solution;
};

TEST_P(CountBinarySubstringsTest, Example1) {
  string s = "00110011";
  int expected = 6;
  EXPECT_EQ(expected, solution.countBinarySubstrings(s));
}

TEST_P(CountBinarySubstringsTest, Example2) {
  string s = "10101";
  int expected = 4;
  EXPECT_EQ(expected, solution.countBinarySubstrings(s));
}

TEST_P(CountBinarySubstringsTest, SingleChar) {
  string s = "0";
  int expected = 0;
  EXPECT_EQ(expected, solution.countBinarySubstrings(s));
}

TEST_P(CountBinarySubstringsTest, TwoSameChars) {
  string s = "00";
  int expected = 0;
  EXPECT_EQ(expected, solution.countBinarySubstrings(s));
}

TEST_P(CountBinarySubstringsTest, TwoDiffChars) {
  string s = "01";
  int expected = 1;
  EXPECT_EQ(expected, solution.countBinarySubstrings(s));
}

TEST_P(CountBinarySubstringsTest, AllZerosThenAllOnes) {
  string s = "000111";
  int expected = 3;  // "01", "0011", "000111"
  EXPECT_EQ(expected, solution.countBinarySubstrings(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountBinarySubstringsTest,
    ::testing::ValuesIn(CountBinarySubstringsSolution().getStrategyNames()));

}  // namespace problem_696
}  // namespace leetcode
