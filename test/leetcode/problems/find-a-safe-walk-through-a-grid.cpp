#include "leetcode/problems/find-a-safe-walk-through-a-grid.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3286 {

class FindASafeWalkThroughAGridTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindASafeWalkThroughAGridSolution solution;
};

TEST_P(FindASafeWalkThroughAGridTest, Example1) {
  vector<vector<int>> grid = {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};
  int health = 1;
  EXPECT_TRUE(solution.findSafeWalk(grid, health));
}

TEST_P(FindASafeWalkThroughAGridTest, Example2) {
  vector<vector<int>> grid = {{0,1,1,0,0,0},{1,0,1,0,0,0},{0,1,1,1,0,1},{0,0,1,0,1,0}};
  int health = 3;
  EXPECT_FALSE(solution.findSafeWalk(grid, health));
}

TEST_P(FindASafeWalkThroughAGridTest, Example3) {
  vector<vector<int>> grid = {{1,1,1},{1,0,1},{1,1,1}};
  int health = 5;
  EXPECT_TRUE(solution.findSafeWalk(grid, health));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindASafeWalkThroughAGridTest,
    ::testing::ValuesIn(FindASafeWalkThroughAGridSolution().getStrategyNames()));

}  // namespace problem_3286
}  // namespace leetcode
