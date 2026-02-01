#include "leetcode/problems/unique-paths-ii.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_63 {

class UniquePathsIiTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  UniquePathsIiSolution solution;
};

// 示例 1: 3x3 网格，中间有障碍物
TEST_P(UniquePathsIiTest, Example1) {
  vector<vector<int>> obstacleGrid = {
      {0, 0, 0},
      {0, 1, 0},
      {0, 0, 0}
  };
  EXPECT_EQ(2, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 示例 2: 2x2 网格，右上角有障碍物
TEST_P(UniquePathsIiTest, Example2) {
  vector<vector<int>> obstacleGrid = {
      {0, 1},
      {0, 0}
  };
  EXPECT_EQ(1, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：1x1 网格，无障碍物
TEST_P(UniquePathsIiTest, SingleCellNoObstacle) {
  vector<vector<int>> obstacleGrid = {{0}};
  EXPECT_EQ(1, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：1x1 网格，有障碍物
TEST_P(UniquePathsIiTest, SingleCellWithObstacle) {
  vector<vector<int>> obstacleGrid = {{1}};
  EXPECT_EQ(0, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：起点有障碍物
TEST_P(UniquePathsIiTest, ObstacleAtStart) {
  vector<vector<int>> obstacleGrid = {
      {1, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
  };
  EXPECT_EQ(0, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：终点有障碍物
TEST_P(UniquePathsIiTest, ObstacleAtEnd) {
  vector<vector<int>> obstacleGrid = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 1}
  };
  EXPECT_EQ(0, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：只有一行
TEST_P(UniquePathsIiTest, SingleRow) {
  vector<vector<int>> obstacleGrid = {{0, 0, 0, 0}};
  EXPECT_EQ(1, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：只有一行且有障碍物
TEST_P(UniquePathsIiTest, SingleRowWithObstacle) {
  vector<vector<int>> obstacleGrid = {{0, 0, 1, 0}};
  EXPECT_EQ(0, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：只有一列
TEST_P(UniquePathsIiTest, SingleColumn) {
  vector<vector<int>> obstacleGrid = {
      {0},
      {0},
      {0},
      {0}
  };
  EXPECT_EQ(1, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：只有一列且有障碍物
TEST_P(UniquePathsIiTest, SingleColumnWithObstacle) {
  vector<vector<int>> obstacleGrid = {
      {0},
      {0},
      {1},
      {0}
  };
  EXPECT_EQ(0, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：整个网格都是障碍物
TEST_P(UniquePathsIiTest, AllObstacles) {
  vector<vector<int>> obstacleGrid = {
      {1, 1},
      {1, 1}
  };
  EXPECT_EQ(0, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 边界情况：无障碍物
TEST_P(UniquePathsIiTest, NoObstacles) {
  vector<vector<int>> obstacleGrid = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
  };
  EXPECT_EQ(6, solution.uniquePathsWithObstacles(obstacleGrid));
}

// 复杂情况：多条路径且有多个障碍物
TEST_P(UniquePathsIiTest, MultipleObstacles) {
  vector<vector<int>> obstacleGrid = {
      {0, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 0}
  };
  EXPECT_EQ(4, solution.uniquePathsWithObstacles(obstacleGrid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, UniquePathsIiTest,
    ::testing::ValuesIn(UniquePathsIiSolution().getStrategyNames()));

}  // namespace problem_63
}  // namespace leetcode
