
#include "leetcode/problems/largest-magic-square.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1895 {

class LargestMagicSquareTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LargestMagicSquareSolution solution;
};

TEST_P(LargestMagicSquareTest, Example1) {
  vector<vector<int>> grid = {{7, 1, 4, 5, 6},
                              {2, 5, 1, 6, 4},
                              {1, 5, 4, 3, 2},
                              {1, 2, 7, 3, 4}};
  int expected = 3;
  int result = solution.largestMagicSquare(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(LargestMagicSquareTest, Example2) {
  vector<vector<int>> grid = {{5, 1, 3, 1},
                              {9, 3, 3, 1},
                              {1, 3, 3, 8}};
  int expected = 2;
  int result = solution.largestMagicSquare(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(LargestMagicSquareTest, SingleElement) {
  vector<vector<int>> grid = {{42}};
  int expected = 1;
  int result = solution.largestMagicSquare(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(LargestMagicSquareTest, AllOnes2x2) {
  vector<vector<int>> grid = {{1, 1},
                              {1, 1}};
  int expected = 2;
  int result = solution.largestMagicSquare(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(LargestMagicSquareTest, NoMagicSquareLargerThan1) {
  vector<vector<int>> grid = {{1, 2},
                              {3, 4}};
  int expected = 1;
  int result = solution.largestMagicSquare(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(LargestMagicSquareTest, LargeMagicSquare) {
  // 3x3 magic square
  vector<vector<int>> grid = {{2, 7, 6},
                              {9, 5, 1},
                              {4, 3, 8}};
  int expected = 3;
  int result = solution.largestMagicSquare(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(LargestMagicSquareTest, RectangularGrid) {
  vector<vector<int>> grid = {{1, 1, 1, 1},
                              {1, 1, 1, 1},
                              {1, 1, 1, 1}};
  // 3x3 幻方无法容纳，因为只有3行4列，最大k=3（行数3），但列数4，可以尝试3x3，检查是否幻方
  // 所有元素为1，任何子矩阵都是幻方，最大k=min(3,4)=3
  int expected = 3;
  int result = solution.largestMagicSquare(grid);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LargestMagicSquareTest,
    ::testing::ValuesIn(LargestMagicSquareSolution().getStrategyNames()));

}  // namespace problem_1895
}  // namespace leetcode
