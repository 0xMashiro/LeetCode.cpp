
#include "leetcode/problems/magic-squares-in-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_840 {

class MagicSquaresInGridTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MagicSquaresInGridSolution solution;
};

TEST_P(MagicSquaresInGridTest, Example1) {
  vector<vector<int>> grid = {{4,3,8,4},{9,5,1,9},{2,7,6,2}};
  int expected = 1;
  int result = solution.numMagicSquaresInside(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(MagicSquaresInGridTest, Example2) {
  vector<vector<int>> grid = {{8}};
  int expected = 0;
  int result = solution.numMagicSquaresInside(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(MagicSquaresInGridTest, EmptyGrid) {
  vector<vector<int>> grid = {};
  int expected = 0;
  int result = solution.numMagicSquaresInside(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(MagicSquaresInGridTest, SingleRow) {
  vector<vector<int>> grid = {{1,2,3,4,5}};
  int expected = 0;
  int result = solution.numMagicSquaresInside(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(MagicSquaresInGridTest, AllOnes) {
  vector<vector<int>> grid = {{1,1,1},{1,1,1},{1,1,1}};
  int expected = 0;  // numbers not distinct, not 1..9
  int result = solution.numMagicSquaresInside(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(MagicSquaresInGridTest, ValidMagicSquare) {
  // A classic 3x3 magic square
  vector<vector<int>> grid = {{8,1,6},{3,5,7},{4,9,2}};
  int expected = 1;
  int result = solution.numMagicSquaresInside(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(MagicSquaresInGridTest, TwoMagicSquares) {
  // Grid containing two magic squares (non-overlapping)
  vector<vector<int>> grid = {
    {8,1,6,0,0},
    {3,5,7,0,0},
    {4,9,2,0,0},
    {0,0,0,8,1,6},
    {0,0,0,3,5,7},
    {0,0,0,4,9,2}
  };
  // Actually the grid is 6x5? Wait need to check dimensions.
  // Let's create a 6x6 grid with two magic squares at (0,0) and (3,3)
  grid = {
    {8,1,6,0,0,0},
    {3,5,7,0,0,0},
    {4,9,2,0,0,0},
    {0,0,0,8,1,6},
    {0,0,0,3,5,7},
    {0,0,0,4,9,2}
  };
  int expected = 2;
  int result = solution.numMagicSquaresInside(grid);
  EXPECT_EQ(expected, result);
}

TEST_P(MagicSquaresInGridTest, GridWithZeroAndLargeNumbers) {
  vector<vector<int>> grid = {
    {4,3,8,4},
    {9,5,1,9},
    {2,7,6,2},
    {0,15,14,13}
  };
  int expected = 1;
  int result = solution.numMagicSquaresInside(grid);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MagicSquaresInGridTest,
    ::testing::ValuesIn(MagicSquaresInGridSolution().getStrategyNames()));

}  // namespace problem_840
}  // namespace leetcode