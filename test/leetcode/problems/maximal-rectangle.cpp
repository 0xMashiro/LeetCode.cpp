#include "leetcode/problems/maximal-rectangle.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_85 {

class MaximalRectangleTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximalRectangleSolution solution;
};

TEST_P(MaximalRectangleTest, Example1) {
  vector<vector<char>> matrix = {
      {'1', '0', '1', '0', '0'},
      {'1', '0', '1', '1', '1'},
      {'1', '1', '1', '1', '1'},
      {'1', '0', '0', '1', '0'}};
  int expected = 6;
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

TEST_P(MaximalRectangleTest, Example2) {
  vector<vector<char>> matrix = {{'0'}};
  int expected = 0;
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

TEST_P(MaximalRectangleTest, Example3) {
  vector<vector<char>> matrix = {{'1'}};
  int expected = 1;
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

TEST_P(MaximalRectangleTest, AllOnes) {
  vector<vector<char>> matrix = {
      {'1', '1', '1'},
      {'1', '1', '1'},
      {'1', '1', '1'}};
  int expected = 9;  // 3x3 = 9
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

TEST_P(MaximalRectangleTest, AllZeros) {
  vector<vector<char>> matrix = {
      {'0', '0', '0'},
      {'0', '0', '0'},
      {'0', '0', '0'}};
  int expected = 0;
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

TEST_P(MaximalRectangleTest, SingleRow) {
  vector<vector<char>> matrix = {{'1', '0', '1', '1', '0', '1'}};
  // 最大矩形是连续的 '1'：位置 2-3，高度为1，宽度为2，面积为2
  int expected = 2;
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

TEST_P(MaximalRectangleTest, SingleColumn) {
  vector<vector<char>> matrix = {{'1'}, {'1'}, {'0'}, {'1'}, {'1'}};
  // 最大矩形是列中连续的 '1'：位置 0-1，高度为2，宽度为1，面积为2
  int expected = 2;
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

TEST_P(MaximalRectangleTest, LargeRectangle) {
  // 4x5 矩阵，包含一个 3x3 的全1矩形（行0-2，列1-3）
  vector<vector<char>> matrix = {
      {'0', '1', '1', '1', '0'},
      {'1', '1', '1', '1', '1'},
      {'0', '1', '1', '1', '0'},
      {'0', '0', '1', '0', '0'}};
  // 最大矩形是 3x3 = 9
  int expected = 9;
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

TEST_P(MaximalRectangleTest, Checkerboard) {
  // 棋盘格，没有连续的矩形
  vector<vector<char>> matrix = {
      {'1', '0', '1'},
      {'0', '1', '0'},
      {'1', '0', '1'}};
  int expected = 1;  // 每个单独的 '1' 都是面积为1的矩形
  EXPECT_EQ(expected, solution.maximalRectangle(matrix));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximalRectangleTest,
    ::testing::ValuesIn(MaximalRectangleSolution().getStrategyNames()));

}  // namespace problem_85
}  // namespace leetcode