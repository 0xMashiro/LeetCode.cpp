
#include "leetcode/problems/minimum-cost-to-change-the-final-value-of-expression.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1896 {

class MinimumCostToChangeTheFinalValueOfExpressionTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumCostToChangeTheFinalValueOfExpressionSolution solution;
};

// Example 1: "1&(0|1)" -> 1
TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, Example1) {
  string expression = "1&(0|1)";
  int expected = 1;
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

// Example 2: "(0&0)&(0&0&0)" -> 3
TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, Example2) {
  string expression = "(0&0)&(0&0&0)";
  int expected = 3;
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

// Example 3: "(0|(1|0&1))" -> 1
TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, Example3) {
  string expression = "(0|(1|0&1))";
  int expected = 1;
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

// 额外测试：单个字符
TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, SingleZero) {
  string expression = "0";
  int expected = 1;  // 0->1需要1次
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, SingleOne) {
  string expression = "1";
  int expected = 1;  // 1->0需要1次
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

// 额外测试：简单运算
TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, SimpleAnd) {
  string expression = "1&1";
  int expected = 1;  // 1&1=1，需要变成0，改&为|即可
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, SimpleOr) {
  string expression = "0|0";
  int expected = 1;  // 0|0=0，需要变成1，改|为&不行，需要改叶子
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

// 测试：嵌套括号
TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, NestedParens) {
  string expression = "((1))";
  int expected = 1;
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

// 测试：复杂表达式
TEST_P(MinimumCostToChangeTheFinalValueOfExpressionTest, ComplexExpression) {
  string expression = "1|1|(0&0)&1";
  // 1|1|(0&0)&1 = 1|1|0&1 = 1|0&1 = 1&1 = 1
  // 需要变成0
  int expected = 1;  // 改最后的&为|，然后... 或者改某个|为&
  EXPECT_EQ(expected, solution.minOperationsToFlip(expression));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumCostToChangeTheFinalValueOfExpressionTest,
    ::testing::ValuesIn(MinimumCostToChangeTheFinalValueOfExpressionSolution().getStrategyNames()));

}  // namespace problem_1896
}  // namespace leetcode
