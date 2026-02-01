#include "leetcode/problems/queens-that-can-attack-the-king.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1222 {

class QueensThatCanAttackTheKingTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  QueensThatCanAttackTheKingSolution solution;
};

// Helper to compare results (order doesn't matter)
void sortResult(vector<vector<int>>& result) {
  sort(result.begin(), result.end(), [](const vector<int>& a, const vector<int>& b) {
    if (a[0] != b[0]) return a[0] < b[0];
    return a[1] < b[1];
  });
}

// Example 1 from problem description
TEST_P(QueensThatCanAttackTheKingTest, Example1) {
  vector<vector<int>> queens = {{0,1},{1,0},{4,0},{0,4},{3,3},{2,4}};
  vector<int> king = {0,0};
  vector<vector<int>> expected = {{0,1},{1,0},{3,3}};
  
  vector<vector<int>> result = solution.queensAttacktheKing(queens, king);
  sortResult(result);
  sortResult(expected);
  
  EXPECT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], result[i]);
  }
}

// Example 2 from problem description
TEST_P(QueensThatCanAttackTheKingTest, Example2) {
  vector<vector<int>> queens = {{0,0},{1,1},{2,2},{3,4},{3,5},{4,4},{4,5}};
  vector<int> king = {3,3};
  vector<vector<int>> expected = {{2,2},{3,4},{4,4}};
  
  vector<vector<int>> result = solution.queensAttacktheKing(queens, king);
  sortResult(result);
  sortResult(expected);
  
  EXPECT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], result[i]);
  }
}

// Single queen that can attack
TEST_P(QueensThatCanAttackTheKingTest, SingleQueen) {
  vector<vector<int>> queens = {{0,0}};
  vector<int> king = {0,7};
  vector<vector<int>> expected = {{0,0}};
  
  vector<vector<int>> result = solution.queensAttacktheKing(queens, king);
  sortResult(result);
  sortResult(expected);
  
  EXPECT_EQ(expected, result);
}

// Queen blocked by another queen
TEST_P(QueensThatCanAttackTheKingTest, BlockedQueen) {
  // Two queens in same direction, only closest can attack
  vector<vector<int>> queens = {{0,0},{0,5}};
  vector<int> king = {0,7};
  vector<vector<int>> expected = {{0,5}};  // Only the closer one can attack
  
  vector<vector<int>> result = solution.queensAttacktheKing(queens, king);
  sortResult(result);
  sortResult(expected);
  
  EXPECT_EQ(expected, result);
}

// King in center, queens in all 8 directions (one per direction)
TEST_P(QueensThatCanAttackTheKingTest, KingInCenter) {
  // King at (3,3), one queen in each of 8 directions
  // Horizontal: (3,0) left, (3,7) right
  // Vertical: (0,3) up, (7,3) down
  // Diagonal: (0,0) up-left, (6,6) down-right, (0,6) up-right, (6,0) down-left
  vector<vector<int>> queens = {{3,0},{3,7},{0,3},{7,3},{0,0},{6,6},{0,6},{6,0}};
  vector<int> king = {3,3};
  // All 8 queens can attack (one per direction)
  vector<vector<int>> expected = {{3,0},{3,7},{0,3},{7,3},{0,0},{6,6},{0,6},{6,0}};
  
  vector<vector<int>> result = solution.queensAttacktheKing(queens, king);
  sortResult(result);
  sortResult(expected);
  
  EXPECT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], result[i]);
  }
}

// No queen can attack
TEST_P(QueensThatCanAttackTheKingTest, NoAttack) {
  // Queens not in same row/col/diagonal as king
  vector<vector<int>> queens = {{0,2},{1,3},{2,0}};
  vector<int> king = {5,5};
  vector<vector<int>> expected = {};
  
  vector<vector<int>> result = solution.queensAttacktheKing(queens, king);
  
  EXPECT_TRUE(result.empty());
}

// Diagonal attack test - queens in both diagonal directions
TEST_P(QueensThatCanAttackTheKingTest, DiagonalAttack) {
  // King at (3,3)
  // {2,2} is up-left direction, {5,5} is down-right direction
  // They are in different directions, so both can attack
  vector<vector<int>> queens = {{0,0},{2,2},{5,5}};
  vector<int> king = {3,3};
  vector<vector<int>> expected = {{2,2},{5,5}};  // Both directions
  
  vector<vector<int>> result = solution.queensAttacktheKing(queens, king);
  sortResult(result);
  sortResult(expected);
  
  EXPECT_EQ(expected, result);
}

// King at corner - closest queens in each direction can attack
TEST_P(QueensThatCanAttackTheKingTest, KingAtCorner) {
  // King at (0,0)
  // {0,1} blocks {0,7} (same row, right direction)
  // {1,0} blocks {7,0} (same col, down direction)
  // {1,1} is the only one on diagonal
  vector<vector<int>> queens = {{0,7},{7,0},{7,7},{0,1},{1,0},{1,1}};
  vector<int> king = {0,0};
  // Closest queens in each direction can attack
  vector<vector<int>> expected = {{0,1},{1,0},{1,1}};
  
  vector<vector<int>> result = solution.queensAttacktheKing(queens, king);
  sortResult(result);
  sortResult(expected);
  
  EXPECT_EQ(expected.size(), result.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(expected[i], result[i]);
  }
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode,
    QueensThatCanAttackTheKingTest,
    ::testing::ValuesIn(QueensThatCanAttackTheKingSolution().getStrategyNames()));

}  // namespace problem_1222
}  // namespace leetcode
