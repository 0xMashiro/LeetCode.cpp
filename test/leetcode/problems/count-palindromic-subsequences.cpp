
#include "leetcode/problems/count-palindromic-subsequences.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2484 {

class CountPalindromicSubsequencesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountPalindromicSubsequencesSolution solution;
};

TEST_P(CountPalindromicSubsequencesTest, Example1) {
  string s = "103301";
  int expected = 2;
  EXPECT_EQ(expected, solution.countPalindromes(s));
}

TEST_P(CountPalindromicSubsequencesTest, Example2) {
  string s = "0000000";
  int expected = 21;
  EXPECT_EQ(expected, solution.countPalindromes(s));
}

TEST_P(CountPalindromicSubsequencesTest, Example3) {
  string s = "9999900000";
  int expected = 2;
  EXPECT_EQ(expected, solution.countPalindromes(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountPalindromicSubsequencesTest,
    ::testing::ValuesIn(CountPalindromicSubsequencesSolution().getStrategyNames()));

}  // namespace problem_2484
}  // namespace leetcode
