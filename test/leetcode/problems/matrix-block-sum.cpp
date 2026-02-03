#include "leetcode/problems/matrix-block-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1314 {

class MatrixBlockSumTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MatrixBlockSumSolution solution;
};

// Example 1: k = 1
TEST_P(MatrixBlockSumTest, Example1) {
  vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int k = 1;
  vector<vector<int>> expected = {{12, 21, 16}, {27, 45, 33}, {24, 39, 28}};
  vector<vector<int>> result = solution.matrixBlockSum(mat, k);
  EXPECT_EQ(expected, result);
}

// Example 2: k = 2 (覆盖整个矩阵)
TEST_P(MatrixBlockSumTest, Example2) {
  vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int k = 2;
  vector<vector<int>> expected = {{45, 45, 45}, {45, 45, 45}, {45, 45, 45}};
  vector<vector<int>> result = solution.matrixBlockSum(mat, k);
  EXPECT_EQ(expected, result);
}

// Edge case: 1x1 matrix
TEST_P(MatrixBlockSumTest, SingleElement) {
  vector<vector<int>> mat = {{5}};
  int k = 1;
  vector<vector<int>> expected = {{5}};
  vector<vector<int>> result = solution.matrixBlockSum(mat, k);
  EXPECT_EQ(expected, result);
}

// Edge case: k = 0 (只包含自己)
TEST_P(MatrixBlockSumTest, KIsZero) {
  vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int k = 0;
  vector<vector<int>> expected = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<vector<int>> result = solution.matrixBlockSum(mat, k);
  EXPECT_EQ(expected, result);
}

// Edge case: Single row
TEST_P(MatrixBlockSumTest, SingleRow) {
  vector<vector<int>> mat = {{1, 2, 3, 4, 5}};
  int k = 1;
  vector<vector<int>> expected = {{3, 6, 9, 12, 9}};
  vector<vector<int>> result = solution.matrixBlockSum(mat, k);
  EXPECT_EQ(expected, result);
}

// Edge case: Single column
TEST_P(MatrixBlockSumTest, SingleColumn) {
  vector<vector<int>> mat = {{1}, {2}, {3}, {4}, {5}};
  int k = 1;
  vector<vector<int>> expected = {{3}, {6}, {9}, {12}, {9}};
  vector<vector<int>> result = solution.matrixBlockSum(mat, k);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MatrixBlockSumTest,
    ::testing::ValuesIn(MatrixBlockSumSolution().getStrategyNames()));

}  // namespace problem_1314
}  // namespace leetcode
