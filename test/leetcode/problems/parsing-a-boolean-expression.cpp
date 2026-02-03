#include "leetcode/problems/parsing-a-boolean-expression.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1106 {

class ParsingABooleanExpressionTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ParsingABooleanExpressionSolution solution;
};

TEST_P(ParsingABooleanExpressionTest, Example1) {
  string expression = "&(|(f))";
  EXPECT_FALSE(solution.parseBoolExpr(expression));
}

TEST_P(ParsingABooleanExpressionTest, Example2) {
  string expression = "|(f,f,f,t)";
  EXPECT_TRUE(solution.parseBoolExpr(expression));
}

TEST_P(ParsingABooleanExpressionTest, Example3) {
  string expression = "!(&(f,t))";
  EXPECT_TRUE(solution.parseBoolExpr(expression));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ParsingABooleanExpressionTest,
    ::testing::ValuesIn(ParsingABooleanExpressionSolution().getStrategyNames()));

}  // namespace problem_1106
}  // namespace leetcode
