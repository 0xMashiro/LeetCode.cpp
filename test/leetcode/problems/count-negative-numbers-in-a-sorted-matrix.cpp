#include "leetcode/problems/count-negative-numbers-in-a-sorted-matrix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1351 {

class CountNegativeNumbersInASortedMatrixTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountNegativeNumbersInASortedMatrixSolution solution;
};

TEST_P(CountNegativeNumbersInASortedMatrixTest, Example1) {
  vector<vector<int>> grid = {{4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}};
  int expected = 8;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

TEST_P(CountNegativeNumbersInASortedMatrixTest, Example2) {
  vector<vector<int>> grid = {{3, 2}, {1, 0}};
  int expected = 0;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试全正数矩阵
TEST_P(CountNegativeNumbersInASortedMatrixTest, AllPositive) {
  vector<vector<int>> grid = {{5, 4, 3}, {4, 3, 2}, {3, 2, 1}};
  int expected = 0;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试全负数矩阵
TEST_P(CountNegativeNumbersInASortedMatrixTest, AllNegative) {
  vector<vector<int>> grid = {{-1, -2, -3}, {-2, -3, -4}, {-3, -4, -5}};
  int expected = 9;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试单行矩阵
TEST_P(CountNegativeNumbersInASortedMatrixTest, SingleRow) {
  vector<vector<int>> grid = {{5, 4, 3, 2, 1, 0, -1, -2}};
  int expected = 2;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试单列矩阵
TEST_P(CountNegativeNumbersInASortedMatrixTest, SingleColumn) {
  vector<vector<int>> grid = {{5}, {4}, {3}, {2}, {1}, {0}, {-1}, {-2}};
  int expected = 2;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试混合矩阵，负数在中间
TEST_P(CountNegativeNumbersInASortedMatrixTest, Mixed) {
  vector<vector<int>> grid = {{5, 4, 3, 2}, {4, 3, 2, 1}, {3, 2, 1, -1}, {2, 1, -1, -2}};
  int expected = 3;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试边界情况：1x1 正数
TEST_P(CountNegativeNumbersInASortedMatrixTest, SinglePositive) {
  vector<vector<int>> grid = {{100}};
  int expected = 0;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试边界情况：1x1 负数
TEST_P(CountNegativeNumbersInASortedMatrixTest, SingleNegative) {
  vector<vector<int>> grid = {{-100}};
  int expected = 1;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试最大规模矩阵（100x100）全正数
TEST_P(CountNegativeNumbersInASortedMatrixTest, LargeAllPositive) {
  vector<vector<int>> grid(100, vector<int>(100, 1));
  int expected = 0;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

// 测试最大规模矩阵（100x100）全负数
TEST_P(CountNegativeNumbersInASortedMatrixTest, LargeAllNegative) {
  vector<vector<int>> grid(100, vector<int>(100, -1));
  int expected = 10000;
  EXPECT_EQ(expected, solution.countNegatives(grid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountNegativeNumbersInASortedMatrixTest,
    ::testing::ValuesIn(CountNegativeNumbersInASortedMatrixSolution().getStrategyNames()));

}  // namespace problem_1351
}  // namespace leetcode