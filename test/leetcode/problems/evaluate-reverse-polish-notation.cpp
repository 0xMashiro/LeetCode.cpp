
#include "leetcode/problems/evaluate-reverse-polish-notation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_150 {

class EvaluateReversePolishNotationTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  EvaluateReversePolishNotationSolution solution;
};

TEST_P(EvaluateReversePolishNotationTest, Example1) {
  vector<string> tokens = {"2", "1", "+", "3", "*"};
  int expected = 9;
  EXPECT_EQ(expected, solution.evalRPN(tokens));
}

TEST_P(EvaluateReversePolishNotationTest, Example2) {
  vector<string> tokens = {"4", "13", "5", "/", "+"};
  int expected = 6;
  EXPECT_EQ(expected, solution.evalRPN(tokens));
}

TEST_P(EvaluateReversePolishNotationTest, Example3) {
  vector<string> tokens = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
  int expected = 22;
  EXPECT_EQ(expected, solution.evalRPN(tokens));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, EvaluateReversePolishNotationTest,
    ::testing::ValuesIn(EvaluateReversePolishNotationSolution().getStrategyNames()));

}  // namespace problem_150
}  // namespace leetcode
