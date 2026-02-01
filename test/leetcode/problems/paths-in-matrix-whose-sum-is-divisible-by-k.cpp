#include "leetcode/problems/paths-in-matrix-whose-sum-is-divisible-by-k.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2435 {

class PathsInMatrixWhoseSumIsDivisibleByKTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PathsInMatrixWhoseSumIsDivisibleByKSolution solution;
};

TEST_P(PathsInMatrixWhoseSumIsDivisibleByKTest, Example1) {
  vector<vector<int>> grid = {{5, 2, 4}, {3, 0, 5}, {0, 7, 2}};
  int k = 3;
  int expected = 2;
  EXPECT_EQ(expected, solution.numberOfPaths(grid, k));
}

TEST_P(PathsInMatrixWhoseSumIsDivisibleByKTest, Example2) {
  vector<vector<int>> grid = {{0, 0}};
  int k = 5;
  int expected = 1;
  EXPECT_EQ(expected, solution.numberOfPaths(grid, k));
}

TEST_P(PathsInMatrixWhoseSumIsDivisibleByKTest, Example3) {
  vector<vector<int>> grid = {{7, 3, 4, 9}, {2, 3, 6, 2}, {2, 3, 7, 0}};
  int k = 1;
  int expected = 10;
  EXPECT_EQ(expected, solution.numberOfPaths(grid, k));
}

TEST_P(PathsInMatrixWhoseSumIsDivisibleByKTest, SingleRow) {
  // 边界：单行矩阵
  vector<vector<int>> grid = {{1, 2, 3, 5}};
  int k = 3;
  // 路径和 = 1+2+3+5 = 11, 11 % 3 = 2, 所以结果为 0
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfPaths(grid, k));
}

TEST_P(PathsInMatrixWhoseSumIsDivisibleByKTest, SingleColumn) {
  // 边界：单列矩阵
  vector<vector<int>> grid = {{1}, {2}, {3}};
  int k = 3;
  // 路径和 = 1+2+3 = 6, 6 % 3 = 0, 所以结果为 1
  int expected = 1;
  EXPECT_EQ(expected, solution.numberOfPaths(grid, k));
}

TEST_P(PathsInMatrixWhoseSumIsDivisibleByKTest, SingleElement) {
  // 边界：单元素矩阵
  vector<vector<int>> grid = {{6}};
  int k = 3;
  // 路径和 = 6, 6 % 3 = 0, 所以结果为 1
  int expected = 1;
  EXPECT_EQ(expected, solution.numberOfPaths(grid, k));
}

TEST_P(PathsInMatrixWhoseSumIsDivisibleByKTest, SingleElementNotDivisible) {
  // 边界：单元素矩阵，不能被 k 整除
  vector<vector<int>> grid = {{5}};
  int k = 3;
  // 路径和 = 5, 5 % 3 = 2, 所以结果为 0
  int expected = 0;
  EXPECT_EQ(expected, solution.numberOfPaths(grid, k));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PathsInMatrixWhoseSumIsDivisibleByKTest,
    ::testing::ValuesIn(PathsInMatrixWhoseSumIsDivisibleByKSolution().getStrategyNames()));

}  // namespace problem_2435
}  // namespace leetcode