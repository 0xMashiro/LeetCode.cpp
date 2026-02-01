
#include "leetcode/problems/detect-cycles-in-2d-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1559 {

class DetectCyclesIn2dGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DetectCyclesIn2dGridSolution solution;
};

// Example 1: 外圈是 'a'，内部是 'b'，形成环
TEST_P(DetectCyclesIn2dGridTest, Example1) {
  vector<vector<char>> grid = {
    {'a', 'a', 'a', 'a'},
    {'a', 'b', 'b', 'a'},
    {'a', 'b', 'b', 'a'},
    {'a', 'a', 'a', 'a'}
  };
  EXPECT_TRUE(solution.containsCycle(grid));
}

// Example 2: 'c' 形成环
TEST_P(DetectCyclesIn2dGridTest, Example2) {
  vector<vector<char>> grid = {
    {'c', 'c', 'c', 'a'},
    {'c', 'd', 'c', 'c'},
    {'c', 'c', 'e', 'c'},
    {'f', 'c', 'c', 'c'}
  };
  EXPECT_TRUE(solution.containsCycle(grid));
}

// Example 3: 没有环
TEST_P(DetectCyclesIn2dGridTest, Example3) {
  vector<vector<char>> grid = {
    {'a', 'b', 'b'},
    {'b', 'z', 'b'},
    {'b', 'b', 'a'}
  };
  EXPECT_FALSE(solution.containsCycle(grid));
}

// 边界情况：1x1 网格，不可能有环
TEST_P(DetectCyclesIn2dGridTest, SingleCell) {
  vector<vector<char>> grid = {{'a'}};
  EXPECT_FALSE(solution.containsCycle(grid));
}

// 边界情况：1x2 网格，不可能有环（长度 < 4）
TEST_P(DetectCyclesIn2dGridTest, TwoCellsRow) {
  vector<vector<char>> grid = {{'a', 'a'}};
  EXPECT_FALSE(solution.containsCycle(grid));
}

// 边界情况：2x2 网格，相同字符形成环
TEST_P(DetectCyclesIn2dGridTest, TwoByTwoCycle) {
  vector<vector<char>> grid = {
    {'a', 'a'},
    {'a', 'a'}
  };
  EXPECT_TRUE(solution.containsCycle(grid));
}

// 边界情况：2x2 网格，不同字符
TEST_P(DetectCyclesIn2dGridTest, TwoByTwoNoCycle) {
  vector<vector<char>> grid = {
    {'a', 'b'},
    {'c', 'd'}
  };
  EXPECT_FALSE(solution.containsCycle(grid));
}

// 直线形状，不可能有环
TEST_P(DetectCyclesIn2dGridTest, StraightLine) {
  vector<vector<char>> grid = {
    {'a', 'a', 'a', 'a', 'a'}
  };
  EXPECT_FALSE(solution.containsCycle(grid));
}

// L 形状，不可能有环
TEST_P(DetectCyclesIn2dGridTest, LShape) {
  vector<vector<char>> grid = {
    {'a', 'a', 'a'},
    {'a', 'b', 'c'},
    {'a', 'd', 'e'}
  };
  EXPECT_FALSE(solution.containsCycle(grid));
}

// 复杂环
TEST_P(DetectCyclesIn2dGridTest, ComplexCycle) {
  vector<vector<char>> grid = {
    {'a', 'a', 'a', 'a', 'a'},
    {'a', 'b', 'b', 'b', 'a'},
    {'a', 'b', 'a', 'b', 'a'},
    {'a', 'b', 'b', 'b', 'a'},
    {'a', 'a', 'a', 'a', 'a'}
  };
  EXPECT_TRUE(solution.containsCycle(grid));
}

// 多个相同字符但不相连
TEST_P(DetectCyclesIn2dGridTest, DisconnectedSameChar) {
  vector<vector<char>> grid = {
    {'a', 'b', 'a'},
    {'c', 'd', 'e'},
    {'a', 'f', 'a'}
  };
  EXPECT_FALSE(solution.containsCycle(grid));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DetectCyclesIn2dGridTest,
    ::testing::ValuesIn(DetectCyclesIn2dGridSolution().getStrategyNames()));

}  // namespace problem_1559
}  // namespace leetcode
