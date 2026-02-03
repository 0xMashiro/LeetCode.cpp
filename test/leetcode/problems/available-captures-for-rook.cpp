
#include "leetcode/problems/available-captures-for-rook.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_999 {

class AvailableCapturesForRookTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AvailableCapturesForRookSolution solution;
};

TEST_P(AvailableCapturesForRookTest, Example1) {
  vector<vector<char>> board = {
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','p','.','.','.','.'},
    {'.','.','.','R','.','.','.','p'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','p','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'}
  };
  EXPECT_EQ(3, solution.numRookCaptures(board));
}

TEST_P(AvailableCapturesForRookTest, Example2) {
  vector<vector<char>> board = {
    {'.','.','.','.','.','.','.','.'},
    {'.','p','p','p','p','p','.','.'},
    {'.','p','p','B','p','p','.','.'},
    {'.','p','B','R','B','p','.','.'},
    {'.','p','p','B','p','p','.','.'},
    {'.','p','p','p','p','p','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'}
  };
  EXPECT_EQ(0, solution.numRookCaptures(board));
}

TEST_P(AvailableCapturesForRookTest, Example3) {
  vector<vector<char>> board = {
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','p','.','.','.','.'},
    {'.','.','.','p','.','.','.','.'},
    {'p','p','.','R','.','p','B','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','B','.','.','.','.'},
    {'.','.','.','p','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'}
  };
  EXPECT_EQ(3, solution.numRookCaptures(board));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AvailableCapturesForRookTest,
    ::testing::ValuesIn(AvailableCapturesForRookSolution().getStrategyNames()));

}  // namespace problem_999
}  // namespace leetcode
