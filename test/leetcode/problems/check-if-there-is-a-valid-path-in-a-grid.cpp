#include "leetcode/problems/check-if-there-is-a-valid-path-in-a-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1391 {

class CheckIfThereIsAValidPathInAGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CheckIfThereIsAValidPathInAGridSolution solution;
};

// 示例 1: 存在有效路径
TEST_P(CheckIfThereIsAValidPathInAGridTest, Example1) {
  vector<vector<int>> grid = {{2, 4, 3}, {6, 5, 2}};
  EXPECT_TRUE(solution.hasValidPath(grid));
}

// 示例 2: 不存在有效路径（起点被孤立）
TEST_P(CheckIfThereIsAValidPathInAGridTest, Example2) {
  vector<vector<int>> grid = {{1, 2, 1}, {1, 2, 1}};
  EXPECT_FALSE(solution.hasValidPath(grid));
}

// 示例 3: 不存在有效路径（中途被卡住）
TEST_P(CheckIfThereIsAValidPathInAGridTest, Example3) {
  vector<vector<int>> grid = {{1, 1, 2}};
  EXPECT_FALSE(solution.hasValidPath(grid));
}

// 边界情况：1x1 网格
TEST_P(CheckIfThereIsAValidPathInAGridTest, SingleCell) {
  vector<vector<int>> grid = {{1}};
  EXPECT_TRUE(solution.hasValidPath(grid));
  
  vector<vector<int>> grid2 = {{2}};
  EXPECT_TRUE(solution.hasValidPath(grid2));
}

// 边界情况：单行网格，存在路径
TEST_P(CheckIfThereIsAValidPathInAGridTest, SingleRowValid) {
  vector<vector<int>> grid = {{1, 1, 1}};
  EXPECT_TRUE(solution.hasValidPath(grid));
}

// 边界情况：单列网格，存在路径
TEST_P(CheckIfThereIsAValidPathInAGridTest, SingleColumnValid) {
  vector<vector<int>> grid = {{2}, {2}, {2}};
  EXPECT_TRUE(solution.hasValidPath(grid));
}

// 边界情况：单行网格，不存在路径
TEST_P(CheckIfThereIsAValidPathInAGridTest, SingleRowInvalid) {
  vector<vector<int>> grid = {{1, 2, 1}};
  EXPECT_FALSE(solution.hasValidPath(grid));
}

// 边界情况：需要转弯的路径
TEST_P(CheckIfThereIsAValidPathInAGridTest, PathWithTurns) {
  // 路径需要转弯的情况
  vector<vector<int>> grid = {
    {4, 1, 3},
    {6, 1, 2}
  };
  EXPECT_TRUE(solution.hasValidPath(grid));
}

// 复杂情况：多条路径可选
TEST_P(CheckIfThereIsAValidPathInAGridTest, MultiplePaths) {
  // 使用 LeetCode 官方示例的路径验证
  // grid = {{2,4,3},{6,5,2}} 应该存在路径
  vector<vector<int>> grid = {
    {2, 4, 3},
    {6, 5, 2}
  };
  EXPECT_TRUE(solution.hasValidPath(grid));
}

// 复杂情况：路径被阻断
TEST_P(CheckIfThereIsAValidPathInAGridTest, BlockedPath) {
  vector<vector<int>> grid = {
    {2, 4, 3},
    {6, 2, 2},  // 中间类型2上下，无法连接到右边
    {1, 1, 1}
  };
  EXPECT_FALSE(solution.hasValidPath(grid));
}

// 测试用例：先向右再向下
TEST_P(CheckIfThereIsAValidPathInAGridTest, RightThenDown) {
  // 路径: (0,0)类型1→(0,1)类型3→(1,1)类型2
  // 类型1(右)→类型3(左)，类型3(下)→类型2(上)
  vector<vector<int>> grid = {
    {1, 3},
    {5, 2}
  };
  EXPECT_TRUE(solution.hasValidPath(grid));
}

// 测试用例：先向下再向右
TEST_P(CheckIfThereIsAValidPathInAGridTest, DownThenRight) {
  // 路径: (0,0)类型2→(1,0)类型6→(1,1)类型1
  // 类型2(下)→类型6(上)，类型6(右)→类型1(左)
  vector<vector<int>> grid = {
    {2, 5},
    {6, 1}
  };
  EXPECT_TRUE(solution.hasValidPath(grid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CheckIfThereIsAValidPathInAGridTest,
    ::testing::ValuesIn(CheckIfThereIsAValidPathInAGridSolution().getStrategyNames()));

}  // namespace problem_1391
}  // namespace leetcode
