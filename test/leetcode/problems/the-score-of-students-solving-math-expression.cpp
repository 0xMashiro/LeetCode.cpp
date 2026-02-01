#include "leetcode/problems/the-score-of-students-solving-math-expression.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2019 {

class TheScoreOfStudentsSolvingMathExpressionTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TheScoreOfStudentsSolvingMathExpressionSolution solution;
};

TEST_P(TheScoreOfStudentsSolvingMathExpressionTest, Example1) {
  std::string s = "7+3*1*2";
  std::vector<int> answers = {20, 13, 42};
  // 正确答案：7+3*1*2 = 7+3*2 = 7+6 = 13
  // 错误答案可能包含：((7+3)*1)*2 = 20
  // 得分：20得2分，13得5分，42得0分，总共7分
  EXPECT_EQ(solution.scoreOfStudents(s, answers), 7);
}

TEST_P(TheScoreOfStudentsSolvingMathExpressionTest, Example2) {
  std::string s = "3+5*2";
  std::vector<int> answers = {13, 0, 10, 13, 13, 16, 16};
  // 正确答案：3+5*2 = 3+10 = 13
  // 错误答案可能包含：(3+5)*2 = 16
  // 得分：13得5分（3次），16得2分（2次），其他0分，总共19分
  EXPECT_EQ(solution.scoreOfStudents(s, answers), 19);
}

TEST_P(TheScoreOfStudentsSolvingMathExpressionTest, Example3) {
  std::string s = "6+0*1";
  std::vector<int> answers = {12, 9, 6, 4, 8, 6};
  // 正确答案：6+0*1 = 6+0 = 6
  // (6+0)*1 = 6 也是6，所以答案6既可能是正确的，也可能是错误的
  // 但规则是优先给5分，所以6都得5分
  // 得分：6得5分（2次），其他0分，总共10分
  EXPECT_EQ(solution.scoreOfStudents(s, answers), 10);
}

TEST_P(TheScoreOfStudentsSolvingMathExpressionTest, SingleOperation) {
  // 简单测试：只有加法
  std::string s = "1+2+3";
  std::vector<int> answers = {6, 6, 9};
  // 正确答案：1+2+3 = 6（加法是结合的，所以只有一种结果）
  // 得分：6得5分（2次），9得0分，总共10分
  EXPECT_EQ(solution.scoreOfStudents(s, answers), 10);
}

TEST_P(TheScoreOfStudentsSolvingMathExpressionTest, OnlyMultiplication) {
  // 简单测试：只有乘法
  std::string s = "2*3*4";
  std::vector<int> answers = {24, 10, 24};
  // 正确答案：2*3*4 = 24（乘法是结合的，所以只有一种结果）
  // 得分：24得5分（2次），10得0分，总共10分
  EXPECT_EQ(solution.scoreOfStudents(s, answers), 10);
}

TEST_P(TheScoreOfStudentsSolvingMathExpressionTest, MixedOperations) {
  // 混合运算
  std::string s = "1+2*3+4";
  std::vector<int> answers = {11, 13, 24, 11};
  // 正确答案：1+2*3+4 = 1+6+4 = 11
  // 错误答案可能包含：
  // (1+2)*3+4 = 9+4 = 13
  // (1+2*3)+4 = 7+4 = 11（正确）
  // 1+(2*3+4) = 1+10 = 11（正确）
  // 1+2*(3+4) = 1+14 = 15
  // (1+2)*(3+4) = 21
  // 1+(2*3)+4 = 11（正确）
  // ((1+2)*3)+4 = 13
  // (1+2)*(3)+4 = 9+4 = 13
  // 得分：11得5分（2次），13得2分（1次），24得0分，总共12分
  EXPECT_EQ(solution.scoreOfStudents(s, answers), 12);
}

TEST_P(TheScoreOfStudentsSolvingMathExpressionTest, AllWrongAnswers) {
  // 所有答案都错误
  std::string s = "1+2";
  std::vector<int> answers = {0, 100, 5};
  // 正确答案：3
  // 只有1+2=3一种可能结果
  // 得分：全部0分
  EXPECT_EQ(solution.scoreOfStudents(s, answers), 0);
}

TEST_P(TheScoreOfStudentsSolvingMathExpressionTest, AllCorrectAnswers) {
  // 所有答案都正确
  std::string s = "5+5";
  std::vector<int> answers = {10, 10, 10, 10};
  // 正确答案：10
  // 得分：全部5分，总共20分
  EXPECT_EQ(solution.scoreOfStudents(s, answers), 20);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TheScoreOfStudentsSolvingMathExpressionTest,
    ::testing::ValuesIn(TheScoreOfStudentsSolvingMathExpressionSolution().getStrategyNames()));

}  // namespace problem_2019
}  // namespace leetcode
