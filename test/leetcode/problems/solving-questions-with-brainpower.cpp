
#include "leetcode/problems/solving-questions-with-brainpower.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2140 {

class SolvingQuestionsWithBrainpowerTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SolvingQuestionsWithBrainpowerSolution solution;
};

TEST_P(SolvingQuestionsWithBrainpowerTest, Example1) {
  vector<vector<int>> questions = {{3, 2}, {4, 3}, {4, 4}, {2, 5}};
  long long expected = 5;
  EXPECT_EQ(expected, solution.mostPoints(questions));
}

TEST_P(SolvingQuestionsWithBrainpowerTest, Example2) {
  vector<vector<int>> questions = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  long long expected = 7;
  EXPECT_EQ(expected, solution.mostPoints(questions));
}

TEST_P(SolvingQuestionsWithBrainpowerTest, SingleQuestion) {
  // 边界：只有一道题
  vector<vector<int>> questions = {{10, 2}};
  long long expected = 10;
  EXPECT_EQ(expected, solution.mostPoints(questions));
}

TEST_P(SolvingQuestionsWithBrainpowerTest, AllSkip) {
  // 边界：所有题目的 brainpower 都很大，只能做最后一题
  vector<vector<int>> questions = {{1, 10}, {2, 10}, {3, 10}};
  long long expected = 3;  // 只能做最后一题
  EXPECT_EQ(expected, solution.mostPoints(questions));
}

TEST_P(SolvingQuestionsWithBrainpowerTest, AllSolve) {
  // 边界：所有题目的 brainpower 都是 0，可以全做
  vector<vector<int>> questions = {{1, 0}, {2, 0}, {3, 0}};
  long long expected = 6;  // 1+2+3 = 6
  EXPECT_EQ(expected, solution.mostPoints(questions));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SolvingQuestionsWithBrainpowerTest,
    ::testing::ValuesIn(SolvingQuestionsWithBrainpowerSolution().getStrategyNames()));

}  // namespace problem_2140
}  // namespace leetcode
