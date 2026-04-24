#include "leetcode/problems/sudoku-solver.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_37 {

// 验证 9x9 棋盘是否是一个合法的数独解
static bool isValidSudoku(const vector<vector<char>>& board) {
  int rows[9] = {0}, cols[9] = {0}, boxes[9] = {0};
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] == '.') return false;  // 必须填满
      int digit = board[i][j] - '1';
      int mask = 1 << digit;
      int boxIdx = (i / 3) * 3 + (j / 3);
      // 检查冲突
      if ((rows[i] & mask) || (cols[j] & mask) || (boxes[boxIdx] & mask)) {
        return false;
      }
      rows[i] |= mask;
      cols[j] |= mask;
      boxes[boxIdx] |= mask;
    }
  }
  return true;
}

class SudokuSolverTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SudokuSolverSolution solution;
};

TEST_P(SudokuSolverTest, Example1) {
  vector<vector<char>> board = {
    {'5','3','.','.','7','.','.','.','.'},
    {'6','.','.','1','9','5','.','.','.'},
    {'.','9','8','.','.','.','.','6','.'},
    {'8','.','.','.','6','.','.','.','3'},
    {'4','.','.','8','.','3','.','.','1'},
    {'7','.','.','.','2','.','.','.','6'},
    {'.','6','.','.','.','.','2','8','.'},
    {'.','.','.','4','1','9','.','.','5'},
    {'.','.','.','.','8','.','.','7','9'}
  };

  solution.solveSudoku(board);

  // 必须合法且填满
  EXPECT_TRUE(isValidSudoku(board));

  // 检查与预期输出一致
  vector<vector<char>> expected = {
    {'5','3','4','6','7','8','9','1','2'},
    {'6','7','2','1','9','5','3','4','8'},
    {'1','9','8','3','4','2','5','6','7'},
    {'8','5','9','7','6','1','4','2','3'},
    {'4','2','6','8','5','3','7','9','1'},
    {'7','1','3','9','2','4','8','5','6'},
    {'9','6','1','5','3','7','2','8','4'},
    {'2','8','7','4','1','9','6','3','5'},
    {'3','4','5','2','8','6','1','7','9'}
  };
  EXPECT_EQ(expected, board);
}

TEST_P(SudokuSolverTest, SelfAuthoredSingleEmpty) {
  // 只有最后一格为空的情况
  vector<vector<char>> board = {
    {'1','2','3','4','5','6','7','8','9'},
    {'4','5','6','7','8','9','1','2','3'},
    {'7','8','9','1','2','3','4','5','6'},
    {'2','3','4','5','6','7','8','9','1'},
    {'5','6','7','8','9','1','2','3','4'},
    {'8','9','1','2','3','4','5','6','7'},
    {'3','4','5','6','7','8','9','1','2'},
    {'6','7','8','9','1','2','3','4','5'},
    {'9','1','2','3','4','5','6','7','.'}
  };

  solution.solveSudoku(board);
  EXPECT_TRUE(isValidSudoku(board));
  EXPECT_EQ(board[8][8], '8');
}

TEST_P(SudokuSolverTest, SelfAuthoredEmptyBoard) {
  // 空棋盘（全 '.'）—— 检查能否正确求解
  vector<vector<char>> board(9, vector<char>(9, '.'));

  solution.solveSudoku(board);
  EXPECT_TRUE(isValidSudoku(board));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SudokuSolverTest,
    ::testing::ValuesIn(SudokuSolverSolution().getStrategyNames()));

}  // namespace problem_37
}  // namespace leetcode
