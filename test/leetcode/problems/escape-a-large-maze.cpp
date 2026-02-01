#include "leetcode/problems/escape-a-large-maze.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1036 {

class EscapeALargeMazeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  EscapeALargeMazeSolution solution;
};

TEST_P(EscapeALargeMazeTest, Example1) {
  vector<vector<int>> blocked = {{0, 1}, {1, 0}};
  vector<int> source = {0, 0};
  vector<int> target = {0, 2};
  EXPECT_FALSE(solution.isEscapePossible(blocked, source, target));
}

TEST_P(EscapeALargeMazeTest, Example2) {
  vector<vector<int>> blocked = {};
  vector<int> source = {0, 0};
  vector<int> target = {999999, 999999};
  EXPECT_TRUE(solution.isEscapePossible(blocked, source, target));
}

TEST_P(EscapeALargeMazeTest, EmptyBlocked) {
  vector<vector<int>> blocked = {};
  vector<int> source = {0, 0};
  vector<int> target = {1, 1};
  EXPECT_TRUE(solution.isEscapePossible(blocked, source, target));
}

TEST_P(EscapeALargeMazeTest, SourceBlockedByWall) {
  // source 被阻挡包围，无法到达 target
  vector<vector<int>> blocked = {
      {0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}, {2, 0}, {0, 2}};
  vector<int> source = {0, 0};
  vector<int> target = {10, 10};
  EXPECT_FALSE(solution.isEscapePossible(blocked, source, target));
}

TEST_P(EscapeALargeMazeTest, CanReachTarget) {
  vector<vector<int>> blocked = {{5, 5}, {5, 6}, {6, 5}};
  vector<int> source = {0, 0};
  vector<int> target = {10, 10};
  EXPECT_TRUE(solution.isEscapePossible(blocked, source, target));
}

TEST_P(EscapeALargeMazeTest, SameRowReachable) {
  vector<vector<int>> blocked = {{0, 2}};
  vector<int> source = {0, 0};
  vector<int> target = {0, 4};
  // 可以绕行: (0,0) -> (1,0) -> (1,1) -> (1,2) -> (1,3) -> (1,4) -> (0,4)
  EXPECT_TRUE(solution.isEscapePossible(blocked, source, target));
}

TEST_P(EscapeALargeMazeTest, LargeGridNoBlocked) {
  vector<vector<int>> blocked = {};
  vector<int> source = {500000, 500000};
  vector<int> target = {999999, 999999};
  EXPECT_TRUE(solution.isEscapePossible(blocked, source, target));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, EscapeALargeMazeTest,
    ::testing::ValuesIn(EscapeALargeMazeSolution().getStrategyNames()));

}  // namespace problem_1036
}  // namespace leetcode
