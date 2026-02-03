#include "leetcode/problems/cyclically-rotating-a-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1914 {

class CyclicallyRotatingAGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CyclicallyRotatingAGridSolution solution;
};

TEST_P(CyclicallyRotatingAGridTest, Example1) {
  vector<vector<int>> grid = {{40, 10}, {30, 20}};
  int k = 1;
  vector<vector<int>> expected = {{10, 20}, {40, 30}};
  vector<vector<int>> result = solution.rotateGrid(grid, k);
  EXPECT_EQ(expected, result);
}

TEST_P(CyclicallyRotatingAGridTest, Example2) {
  vector<vector<int>> grid = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  int k = 2;
  vector<vector<int>> expected = {{3, 4, 8, 12}, {2, 11, 10, 16}, {1, 7, 6, 15}, {5, 9, 13, 14}};
  vector<vector<int>> result = solution.rotateGrid(grid, k);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CyclicallyRotatingAGridTest,
    ::testing::ValuesIn(CyclicallyRotatingAGridSolution().getStrategyNames()));

}  // namespace problem_1914
}  // namespace leetcode
