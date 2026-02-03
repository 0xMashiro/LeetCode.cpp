#include "leetcode/problems/equal-sum-grid-partition-i.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3546 {

class EqualSumGridPartitionITest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  EqualSumGridPartitionISolution solution;
};

TEST_P(EqualSumGridPartitionITest, Example1) {
  // grid = [[1,4],[2,3]], 总和为 10，可以在第0行后水平切割，上半部分和为 5
  vector<vector<int>> grid = {{1, 4}, {2, 3}};
  EXPECT_TRUE(solution.canPartitionGrid(grid));
}

TEST_P(EqualSumGridPartitionITest, Example2) {
  // grid = [[1,3],[2,4]], 总和为 10，但没有切割能使两部分都为 5
  vector<vector<int>> grid = {{1, 3}, {2, 4}};
  EXPECT_FALSE(solution.canPartitionGrid(grid));
}

TEST_P(EqualSumGridPartitionITest, VerticalCut) {
  // 测试垂直切割：[[1,1],[1,1]]，总和为 4，可以在第0列后垂直切割
  vector<vector<int>> grid = {{1, 1}, {1, 1}};
  EXPECT_TRUE(solution.canPartitionGrid(grid));
}

TEST_P(EqualSumGridPartitionITest, SingleRowCannotCut) {
  // 单行网格，无法水平切割（因为需要两部分都非空）
  // 垂直切割：[[1,2,3]]，总和为 6，可以在第0列或第1列后切
  vector<vector<int>> grid = {{1, 2, 3}};
  EXPECT_TRUE(solution.canPartitionGrid(grid));
}

TEST_P(EqualSumGridPartitionITest, SingleColumnCannotCut) {
  // 单列网格，无法垂直切割
  // 水平切割：[[1],[2],[3]]，总和为 6，可以在第0行或第1行后切
  vector<vector<int>> grid = {{1}, {2}, {3}};
  EXPECT_TRUE(solution.canPartitionGrid(grid));
}

TEST_P(EqualSumGridPartitionITest, OddSum) {
  // 总和为奇数，无法平分：[[1,1],[1,2]]，总和为 5
  vector<vector<int>> grid = {{1, 1}, {1, 2}};
  EXPECT_FALSE(solution.canPartitionGrid(grid));
}

TEST_P(EqualSumGridPartitionITest, LargeNumbers) {
  // 大数测试：[[100000,100000],[100000,100000]]，总和为 400000
  vector<vector<int>> grid = {{100000, 100000}, {100000, 100000}};
  EXPECT_TRUE(solution.canPartitionGrid(grid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, EqualSumGridPartitionITest,
    ::testing::ValuesIn(EqualSumGridPartitionISolution().getStrategyNames()));

}  // namespace problem_3546
}  // namespace leetcode
