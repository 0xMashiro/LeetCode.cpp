#include "leetcode/problems/transpose-matrix.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_867 {

class TransposeMatrixTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  TransposeMatrixSolution solution;
};

TEST_P(TransposeMatrixTest, Example1) {
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<vector<int>> expected = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
  EXPECT_EQ(expected, solution.transpose(matrix));
}

TEST_P(TransposeMatrixTest, Example2) {
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}};
  vector<vector<int>> expected = {{1, 4}, {2, 5}, {3, 6}};
  EXPECT_EQ(expected, solution.transpose(matrix));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, TransposeMatrixTest,
    ::testing::ValuesIn(TransposeMatrixSolution().getStrategyNames()));

}  // namespace problem_867
}  // namespace leetcode