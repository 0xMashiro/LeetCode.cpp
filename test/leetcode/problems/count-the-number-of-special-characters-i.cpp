#include "leetcode/problems/count-the-number-of-special-characters-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3120 {

class CountTheNumberOfSpecialCharactersITest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountTheNumberOfSpecialCharactersISolution solution;
};

TEST_P(CountTheNumberOfSpecialCharactersITest, Example1) {
  string word = "aaAbcBC";
  EXPECT_EQ(3, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersITest, Example2) {
  string word = "abc";
  EXPECT_EQ(0, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersITest, Example3) {
  string word = "abBCab";
  EXPECT_EQ(1, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersITest, SelfAuthoredSingleChar) {
  string word = "aA";
  EXPECT_EQ(1, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersITest, SelfAuthoredNoUppercase) {
  string word = "abcdef";
  EXPECT_EQ(0, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersITest, SelfAuthoredAllSpecial) {
  string word = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
  EXPECT_EQ(26, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersITest, SelfAuthoredRepeatedChars) {
  string word = "AAAaaaBBBbbb";
  EXPECT_EQ(2, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersITest, SelfAuthoredSingleLetterRepeated) {
  string word = "zzZZzzZZ";
  EXPECT_EQ(1, solution.numberOfSpecialChars(word));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountTheNumberOfSpecialCharactersITest,
    ::testing::ValuesIn(CountTheNumberOfSpecialCharactersISolution().getStrategyNames()));

}  // namespace problem_3120
}  // namespace leetcode
