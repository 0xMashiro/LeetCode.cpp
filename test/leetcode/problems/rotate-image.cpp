#include "leetcode/problems/rotate-image.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_48 {

class RotateImageTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RotateImageSolution solution;
};

TEST_P(RotateImageTest, Example1) {
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<vector<int>> expected = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
  solution.rotate(matrix);
  EXPECT_EQ(expected, matrix);
}

TEST_P(RotateImageTest, Example2) {
  vector<vector<int>> matrix = {
      {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
  vector<vector<int>> expected = {
      {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}};
  solution.rotate(matrix);
  EXPECT_EQ(expected, matrix);
}

TEST_P(RotateImageTest, SelfAuthoredSingleElement) {
  vector<vector<int>> matrix = {{1}};
  vector<vector<int>> expected = {{1}};
  solution.rotate(matrix);
  EXPECT_EQ(expected, matrix);
}

TEST_P(RotateImageTest, SelfAuthoredTwoByTwo) {
  vector<vector<int>> matrix = {{1, 2}, {3, 4}};
  vector<vector<int>> expected = {{3, 1}, {4, 2}};
  solution.rotate(matrix);
  EXPECT_EQ(expected, matrix);
}

TEST_P(RotateImageTest, SelfAuthoredAllSame) {
  vector<vector<int>> matrix = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  vector<vector<int>> expected = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
  solution.rotate(matrix);
  EXPECT_EQ(expected, matrix);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RotateImageTest,
    ::testing::ValuesIn(RotateImageSolution().getStrategyNames()));

}  // namespace problem_48
}  // namespace leetcode
