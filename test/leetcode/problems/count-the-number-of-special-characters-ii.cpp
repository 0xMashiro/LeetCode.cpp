#include "leetcode/problems/count-the-number-of-special-characters-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3121 {

class CountTheNumberOfSpecialCharactersIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountTheNumberOfSpecialCharactersIiSolution solution;
};

TEST_P(CountTheNumberOfSpecialCharactersIiTest, Example1) {
  std::string word = "aaAbcBC";
  int expected = 3;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, Example2) {
  std::string word = "abc";
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, Example3) {
  std::string word = "AbBCab";
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredSingleLowercase) {
  std::string word = "a";
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredSingleUppercase) {
  std::string word = "A";
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredSimpleValid) {
  std::string word = "aA";
  int expected = 1;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredUppercaseFirst) {
  std::string word = "Aa";
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredMultipleLowercase) {
  std::string word = "aaaA";
  int expected = 1;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredLowercaseAfterUppercase) {
  std::string word = "aAa";
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredMultipleLetters) {
  std::string word = "aAbBcC";
  int expected = 3;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredMixedInvalid) {
  std::string word = "aAbBcCd";
  int expected = 3;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

TEST_P(CountTheNumberOfSpecialCharactersIiTest, SelfAuthoredComplex) {
  // word = "aAbBcCaDdEe"
  // positions:
  // a(0), A(1) -> special for 'a'
  // b(2), B(3) -> special for 'b'
  // c(4), C(5) -> special for 'c'
  // a(6) -> lowercase after 'A'(1), invalidates 'a'
  // D(7), d(8) -> uppercase before lowercase -> invalid for 'd'
  // E(9), e(10) -> uppercase before lowercase -> invalid for 'e'
  // Only 'b' and 'c' remain special -> expected = 2
  std::string word = "aAbBcCaDdEe";
  int expected = 2;
  EXPECT_EQ(expected, solution.numberOfSpecialChars(word));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountTheNumberOfSpecialCharactersIiTest,
    ::testing::ValuesIn(CountTheNumberOfSpecialCharactersIiSolution().getStrategyNames()));

}  // namespace problem_3121
}  // namespace leetcode
