#include "leetcode/problems/maximum-matrix-sum.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1975 {

class MaximumMatrixSumTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumMatrixSumSolution solution;
};

TEST_P(MaximumMatrixSumTest, Example1) {
  vector<vector<int>> matrix = {{1, -1}, {-1, 1}};
  long long expected = 4;
  long long result = solution.maxMatrixSum(matrix);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumMatrixSumTest, Example2) {
  vector<vector<int>> matrix = {{1, 2, 3}, {-1, -2, -3}, {1, 2, 3}};
  long long expected = 16;
  long long result = solution.maxMatrixSum(matrix);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumMatrixSumTest, AllPositive) {
  vector<vector<int>> matrix = {{1, 2}, {3, 4}};
  long long expected = 10;  // 1+2+3+4 = 10
  long long result = solution.maxMatrixSum(matrix);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumMatrixSumTest, AllNegativeEvenCount) {
  vector<vector<int>> matrix = {{-1, -2}, {-3, -4}};
  long long expected = 10;  // 1+2+3+4 = 10
  long long result = solution.maxMatrixSum(matrix);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumMatrixSumTest, AllNegativeOddCount) {
  vector<vector<int>> matrix = {{-1, -2}, {-3, 4}};
  long long expected = 8;  // 1+2+3+4 - 2*1 = 10 - 2 = 8
  long long result = solution.maxMatrixSum(matrix);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumMatrixSumTest, WithZero) {
  vector<vector<int>> matrix = {{-1, -2}, {0, 4}};
  long long expected = 7;  // 1+2+0+4 = 7
  long long result = solution.maxMatrixSum(matrix);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumMatrixSumTest, SingleNegativeWithZero) {
  vector<vector<int>> matrix = {{-1, 0}, {2, 3}};
  long long expected = 6;  // 1+0+2+3 = 6
  long long result = solution.maxMatrixSum(matrix);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumMatrixSumTest, LargeMatrix) {
  // 2x2 matrix with mixed values
  vector<vector<int>> matrix = {{-100000, 50000}, {0, 100000}};
  long long expected = 250000;  // 100000+50000+0+100000 = 250000
  long long result = solution.maxMatrixSum(matrix);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumMatrixSumTest,
    ::testing::ValuesIn(MaximumMatrixSumSolution().getStrategyNames()));

}  // namespace problem_1975
}  // namespace leetcode