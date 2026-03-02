#include "leetcode/problems/minimum-swaps-to-arrange-a-binary-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1536 {

class MinimumSwapsToArrangeABinaryGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MinimumSwapsToArrangeABinaryGridSolution solution;
};

TEST_P(MinimumSwapsToArrangeABinaryGridTest, Example1) {
  vector<vector<int>> grid = {{0, 0, 1}, {1, 1, 0}, {1, 0, 0}};
  int expected = 3;
  EXPECT_EQ(expected, solution.minSwaps(grid));
}

TEST_P(MinimumSwapsToArrangeABinaryGridTest, Example2) {
  vector<vector<int>> grid = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}};
  int expected = -1;
  EXPECT_EQ(expected, solution.minSwaps(grid));
}

TEST_P(MinimumSwapsToArrangeABinaryGridTest, Example3) {
  vector<vector<int>> grid = {{1, 0, 0}, {1, 1, 0}, {1, 1, 1}};
  int expected = 0;
  EXPECT_EQ(expected, solution.minSwaps(grid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MinimumSwapsToArrangeABinaryGridTest,
    ::testing::ValuesIn(MinimumSwapsToArrangeABinaryGridSolution().getStrategyNames()));

}  // namespace problem_1536
}  // namespace leetcode