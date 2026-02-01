
#include "leetcode/problems/search-a-2d-matrix-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_240 {

class SearchA2dMatrixIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SearchA2dMatrixIiSolution solution;
};

// Example 1: target = 5, expected = true
TEST_P(SearchA2dMatrixIiTest, Example1) {
  vector<vector<int>> matrix = {
    {1, 4, 7, 11, 15},
    {2, 5, 8, 12, 19},
    {3, 6, 9, 16, 22},
    {10, 13, 14, 17, 24},
    {18, 21, 23, 26, 30}
  };
  int target = 5;
  EXPECT_TRUE(solution.searchMatrix(matrix, target));
}

// Example 2: target = 20, expected = false
TEST_P(SearchA2dMatrixIiTest, Example2) {
  vector<vector<int>> matrix = {
    {1, 4, 7, 11, 15},
    {2, 5, 8, 12, 19},
    {3, 6, 9, 16, 22},
    {10, 13, 14, 17, 24},
    {18, 21, 23, 26, 30}
  };
  int target = 20;
  EXPECT_FALSE(solution.searchMatrix(matrix, target));
}

// Edge case: single element, found
TEST_P(SearchA2dMatrixIiTest, SingleElementFound) {
  vector<vector<int>> matrix = {{1}};
  EXPECT_TRUE(solution.searchMatrix(matrix, 1));
}

// Edge case: single element, not found
TEST_P(SearchA2dMatrixIiTest, SingleElementNotFound) {
  vector<vector<int>> matrix = {{1}};
  EXPECT_FALSE(solution.searchMatrix(matrix, 2));
}

// Edge case: single row
TEST_P(SearchA2dMatrixIiTest, SingleRow) {
  vector<vector<int>> matrix = {{1, 3, 5, 7, 9}};
  EXPECT_TRUE(solution.searchMatrix(matrix, 5));
  EXPECT_FALSE(solution.searchMatrix(matrix, 6));
}

// Edge case: single column
TEST_P(SearchA2dMatrixIiTest, SingleColumn) {
  vector<vector<int>> matrix = {{1}, {3}, {5}, {7}, {9}};
  EXPECT_TRUE(solution.searchMatrix(matrix, 5));
  EXPECT_FALSE(solution.searchMatrix(matrix, 6));
}

// Edge case: target is the minimum element
TEST_P(SearchA2dMatrixIiTest, TargetMinimum) {
  vector<vector<int>> matrix = {
    {1, 4, 7},
    {2, 5, 8},
    {3, 6, 9}
  };
  EXPECT_TRUE(solution.searchMatrix(matrix, 1));
}

// Edge case: target is the maximum element
TEST_P(SearchA2dMatrixIiTest, TargetMaximum) {
  vector<vector<int>> matrix = {
    {1, 4, 7},
    {2, 5, 8},
    {3, 6, 9}
  };
  EXPECT_TRUE(solution.searchMatrix(matrix, 9));
}

// Edge case: target smaller than all elements
TEST_P(SearchA2dMatrixIiTest, TargetTooSmall) {
  vector<vector<int>> matrix = {
    {10, 20, 30},
    {40, 50, 60},
    {70, 80, 90}
  };
  EXPECT_FALSE(solution.searchMatrix(matrix, 5));
}

// Edge case: target larger than all elements
TEST_P(SearchA2dMatrixIiTest, TargetTooLarge) {
  vector<vector<int>> matrix = {
    {10, 20, 30},
    {40, 50, 60},
    {70, 80, 90}
  };
  EXPECT_FALSE(solution.searchMatrix(matrix, 100));
}

// Edge case: negative numbers
TEST_P(SearchA2dMatrixIiTest, NegativeNumbers) {
  vector<vector<int>> matrix = {
    {-10, -5, 0},
    {-8, -3, 2},
    {-6, -1, 4}
  };
  EXPECT_TRUE(solution.searchMatrix(matrix, -5));
  EXPECT_TRUE(solution.searchMatrix(matrix, -6));
  EXPECT_FALSE(solution.searchMatrix(matrix, -7));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SearchA2dMatrixIiTest,
    ::testing::ValuesIn(SearchA2dMatrixIiSolution().getStrategyNames()));

}  // namespace problem_240
}  // namespace leetcode
