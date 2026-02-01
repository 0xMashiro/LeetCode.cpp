#include "leetcode/problems/matrix-diagonal-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1572 {

class MatrixDiagonalSumTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MatrixDiagonalSumSolution solution;
};

TEST_P(MatrixDiagonalSumTest, Example1) {
  // mat = [[1,2,3],
  //        [4,5,6],
  //        [7,8,9]]
  // Output: 25 (1+5+9+3+7)
  vector<vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  EXPECT_EQ(25, solution.diagonalSum(mat));
}

TEST_P(MatrixDiagonalSumTest, Example2) {
  // mat = [[1,1,1,1],
  //        [1,1,1,1],
  //        [1,1,1,1],
  //        [1,1,1,1]]
  // Output: 8
  vector<vector<int>> mat = {
      {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
  EXPECT_EQ(8, solution.diagonalSum(mat));
}

TEST_P(MatrixDiagonalSumTest, Example3) {
  // mat = [[5]]
  // Output: 5
  vector<vector<int>> mat = {{5}};
  EXPECT_EQ(5, solution.diagonalSum(mat));
}

TEST_P(MatrixDiagonalSumTest, SingleElement) {
  // 单元素矩阵
  vector<vector<int>> mat = {{10}};
  EXPECT_EQ(10, solution.diagonalSum(mat));
}

TEST_P(MatrixDiagonalSumTest, TwoByTwo) {
  // 2x2 矩阵
  // mat = [[1,2],
  //        [3,4]]
  // Output: 1+4+2+3 = 10
  vector<vector<int>> mat = {{1, 2}, {3, 4}};
  EXPECT_EQ(10, solution.diagonalSum(mat));
}

TEST_P(MatrixDiagonalSumTest, LargerMatrix) {
  // 5x5 矩阵，验证奇数大小矩阵的中心元素只计算一次
  vector<vector<int>> mat = {
      {1, 2, 3, 4, 5},
      {6, 7, 8, 9, 10},
      {11, 12, 13, 14, 15},
      {16, 17, 18, 19, 20},
      {21, 22, 23, 24, 25}};
  // 主对角线: 1+7+13+19+25 = 65
  // 副对角线: 5+9+13+17+21 = 65
  // 中心元素 13 被计算两次，减去一次: 65+65-13 = 117
  EXPECT_EQ(117, solution.diagonalSum(mat));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MatrixDiagonalSumTest,
    ::testing::ValuesIn(MatrixDiagonalSumSolution().getStrategyNames()));

}  // namespace problem_1572
}  // namespace leetcode
