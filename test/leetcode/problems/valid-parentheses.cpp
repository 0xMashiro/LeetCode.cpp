#include "leetcode/problems/valid-parentheses.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_20 {

class ValidParenthesesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ValidParenthesesSolution solution;
};

TEST_P(ValidParenthesesTest, Example1) {
  std::string s = "()";
  EXPECT_TRUE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, Example2) {
  std::string s = "()[]{}";
  EXPECT_TRUE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, Example3) {
  std::string s = "(]";
  EXPECT_FALSE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, Example4) {
  std::string s = "([])";
  EXPECT_TRUE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, Example5) {
  std::string s = "([)]";
  EXPECT_FALSE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, EmptyString) {
  std::string s = "";
  EXPECT_TRUE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, OnlyLeftBrackets) {
  std::string s = "((({{{[[[";
  EXPECT_FALSE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, OnlyRightBrackets) {
  std::string s = ")))]]]}}}";
  EXPECT_FALSE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, SingleLeftBracket) {
  std::string s = "(";
  EXPECT_FALSE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, SingleRightBracket) {
  std::string s = ")";
  EXPECT_FALSE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, LongNested) {
  std::string s = "(((((((())))))))";
  EXPECT_TRUE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, LongMixedNested) {
  std::string s = "{[()()]}";
  EXPECT_TRUE(solution.isValid(s));
}

TEST_P(ValidParenthesesTest, MismatchedLong) {
  std::string s = "(((((((()))))))}";
  EXPECT_FALSE(solution.isValid(s));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ValidParenthesesTest,
    ::testing::ValuesIn(ValidParenthesesSolution().getStrategyNames()));

}  // namespace problem_20
}  // namespace leetcode
