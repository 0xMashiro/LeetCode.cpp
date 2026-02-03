#include "leetcode/problems/solve-the-equation.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_640 {

class SolveTheEquationTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SolveTheEquationSolution solution;
};

TEST_P(SolveTheEquationTest, Example1) {
  string equation = "x+5-3+x=6+x-2";
  string expected = "x=2";
  EXPECT_EQ(expected, solution.solveEquation(equation));
}

TEST_P(SolveTheEquationTest, Example2) {
  string equation = "x=x";
  string expected = "Infinite solutions";
  EXPECT_EQ(expected, solution.solveEquation(equation));
}

TEST_P(SolveTheEquationTest, Example3) {
  string equation = "2x=x";
  string expected = "x=0";
  EXPECT_EQ(expected, solution.solveEquation(equation));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SolveTheEquationTest,
    ::testing::ValuesIn(SolveTheEquationSolution().getStrategyNames()));

}  // namespace problem_640
}  // namespace leetcode
