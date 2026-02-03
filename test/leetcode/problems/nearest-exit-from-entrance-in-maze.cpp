
#include "leetcode/problems/nearest-exit-from-entrance-in-maze.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1926 {

class NearestExitFromEntranceInMazeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NearestExitFromEntranceInMazeSolution solution;
};

TEST_P(NearestExitFromEntranceInMazeTest, Example1) {
  // Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
  // Output: 1
  vector<vector<char>> maze = {{'+', '+', '.', '+'}, {'.', '.', '.', '+'}, {'+', '+', '+', '.'}};
  vector<int> entrance = {1, 2};
  EXPECT_EQ(1, solution.nearestExit(maze, entrance));
}

TEST_P(NearestExitFromEntranceInMazeTest, Example2) {
  // Input: maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
  // Output: 2
  vector<vector<char>> maze = {{'+', '+', '+'}, {'.', '.', '.'}, {'+', '+', '+'}};
  vector<int> entrance = {1, 0};
  EXPECT_EQ(2, solution.nearestExit(maze, entrance));
}

TEST_P(NearestExitFromEntranceInMazeTest, Example3) {
  // Input: maze = [[".","+"]], entrance = [0,0]
  // Output: -1
  vector<vector<char>> maze = {{'.', '+'}};
  vector<int> entrance = {0, 0};
  EXPECT_EQ(-1, solution.nearestExit(maze, entrance));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NearestExitFromEntranceInMazeTest,
    ::testing::ValuesIn(NearestExitFromEntranceInMazeSolution().getStrategyNames()));

}  // namespace problem_1926
}  // namespace leetcode
