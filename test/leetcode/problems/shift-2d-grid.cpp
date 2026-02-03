#include "leetcode/problems/shift-2d-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1260 {

class Shift2dGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  Shift2dGridSolution solution;
};

TEST_P(Shift2dGridTest, Example1) {
  vector<vector<int>> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int k = 1;
  vector<vector<int>> expected = {{9, 1, 2}, {3, 4, 5}, {6, 7, 8}};
  EXPECT_EQ(expected, solution.shiftGrid(grid, k));
}

TEST_P(Shift2dGridTest, Example2) {
  vector<vector<int>> grid = {{3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}, {12, 0, 21, 13}};
  int k = 4;
  vector<vector<int>> expected = {{12, 0, 21, 13}, {3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}};
  EXPECT_EQ(expected, solution.shiftGrid(grid, k));
}

TEST_P(Shift2dGridTest, Example3) {
  vector<vector<int>> grid = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int k = 9;
  vector<vector<int>> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  EXPECT_EQ(expected, solution.shiftGrid(grid, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, Shift2dGridTest,
    ::testing::ValuesIn(Shift2dGridSolution().getStrategyNames()));

}  // namespace problem_1260
}  // namespace leetcode
