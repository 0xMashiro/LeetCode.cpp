#include "leetcode/problems/block-placement-queries.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_3161 {

class BlockPlacementQueriesTest
    : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BlockPlacementQueriesSolution solution;
};

TEST_P(BlockPlacementQueriesTest, Example1) {
  vector<vector<int>> queries = {{1, 2}, {2, 3, 3}, {2, 3, 1}, {2, 2, 2}};
  vector<bool> expected = {false, true, true};
  EXPECT_EQ(expected, solution.getResults(queries));
}

TEST_P(BlockPlacementQueriesTest, Example2) {
  vector<vector<int>> queries = {
      {1, 7}, {2, 7, 6}, {1, 2}, {2, 7, 5}, {2, 7, 6}};
  vector<bool> expected = {true, true, false};
  EXPECT_EQ(expected, solution.getResults(queries));
}

TEST_P(BlockPlacementQueriesTest, SelfAuthoredNoObstacle) {
  // No obstacles, block of size 5 in [0, 10]
  vector<vector<int>> queries = {{2, 10, 5}};
  vector<bool> expected = {true};
  EXPECT_EQ(expected, solution.getResults(queries));
}

TEST_P(BlockPlacementQueriesTest, SelfAuthoredBlockExactlyFits) {
  // Obstacle at 5, block of size 5 in [0, 5] → exactly fits from 0 to 5
  vector<vector<int>> queries = {{1, 5}, {2, 5, 5}};
  vector<bool> expected = {true};
  EXPECT_EQ(expected, solution.getResults(queries));
}

TEST_P(BlockPlacementQueriesTest, SelfAuthoredBlockTouchesObstacle) {
  // Obstacle at 5, block of size 5 in [0, 6] → can place [1,6] touching obstacle
  vector<vector<int>> queries = {{1, 5}, {2, 6, 5}};
  vector<bool> expected = {true};
  EXPECT_EQ(expected, solution.getResults(queries));
}

TEST_P(BlockPlacementQueriesTest, SelfAuthoredBlockTooBig) {
  // Obstacle at 3, block of size 4 in [0, 6]
  // gaps: [0,3]=3, [3,6]=3. Max = 3 < 4
  vector<vector<int>> queries = {{1, 3}, {2, 6, 4}};
  vector<bool> expected = {false};
  EXPECT_EQ(expected, solution.getResults(queries));
}

TEST_P(BlockPlacementQueriesTest, SelfAuthoredMultipleObstacles) {
  // Obstacles at 2, 5, 9
  // Gaps: [0,2]=2, [2,5]=3, [5,9]=4
  // Query [2, 8, 3] → gaps within [0,8]: [0,2]=2, [2,5]=3, [5,8]=3. Max=3 >= 3 ✓
  // Query [2, 8, 4] → max gap = 3 < 4 ✗
  vector<vector<int>> queries = {
      {1, 2}, {1, 5}, {1, 9}, {2, 8, 3}, {2, 8, 4}};
  vector<bool> expected = {true, false};
  EXPECT_EQ(expected, solution.getResults(queries));
}

TEST_P(BlockPlacementQueriesTest, SelfAuthoredObstacleAtMaxCoord) {
  // Obstacle at 50000, block of size 50000 in [0, 50000]
  // Gap from 0 to 50000 is 50000, so block fits
  vector<vector<int>> queries = {{1, 50000}, {2, 50000, 50000}};
  vector<bool> expected = {true};
  EXPECT_EQ(expected, solution.getResults(queries));
}

TEST_P(BlockPlacementQueriesTest, SelfAuthoredInterleavedQueries) {
  // Mix of type 1 and type 2 queries
  vector<vector<int>> queries = {
      {1, 3},       // place obstacle at 3
      {2, 10, 4},  // [0,10] max gap = max(3-0=3, 10-3=7) = 7 >= 4 → true
      {1, 8},       // place obstacle at 8, gaps: [0,3]=3, [3,8]=5, [8,...]
      {2, 10, 6},  // [0,10] gaps: [0,3]=3, [3,8]=5, [8,10]=2. Max=5 < 6 → false
      {2, 10, 5},  // max = 5 >= 5 → true
      {2, 3, 3},   // [0,3] gap = 3 >= 3 → true
      {2, 2, 3}    // [0,2] gap = 2 < 3 → false
  };
  vector<bool> expected = {true, false, true, true, false};
  EXPECT_EQ(expected, solution.getResults(queries));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BlockPlacementQueriesTest,
    ::testing::ValuesIn(BlockPlacementQueriesSolution().getStrategyNames()));

}  // namespace problem_3161
}  // namespace leetcode
