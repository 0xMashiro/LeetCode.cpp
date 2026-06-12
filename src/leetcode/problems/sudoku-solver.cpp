#include "leetcode/problems/sudoku-solver.h"

namespace leetcode {
namespace problem_37 {

// ========== Helper: 朴素检查 (row, col) 处放字符 c 是否合法 ==========
static bool isValid(const vector<vector<char>>& board, int row, int col, char c) {
  // 检查行
  for (int j = 0; j < 9; ++j) {
    if (board[row][j] == c) return false;
  }
  // 检查列
  for (int i = 0; i < 9; ++i) {
    if (board[i][col] == c) return false;
  }
  // 检查 3x3 九宫格
  int boxRow = row / 3 * 3;
  int boxCol = col / 3 * 3;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (board[boxRow + i][boxCol + j] == c) return false;
    }
  }
  return true;
}

// ========== Solution 1: 朴素回溯法 ==========
// 思路：从左到右、从上到下扫描每个格子，遇到空格('.')
//       就尝试 '1'-'9'，用 isValid 检查是否合法，递归填下一个空格
// 时间复杂度: O(9^(81-k))，k 为预填数字个数
// 空间复杂度: O(81) 递归栈深度
static bool backtrack1(vector<vector<char>>& board) {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] == '.') {
        for (char c = '1'; c <= '9'; ++c) {
          if (isValid(board, i, j, c)) {
            board[i][j] = c;
            if (backtrack1(board)) return true;
            board[i][j] = '.';  // 回溯
          }
        }
        return false;  // 1-9 都试过不行
      }
    }
  }
  return true;  // 全部填满
}

static void solution1(vector<vector<char>>& board) {
  backtrack1(board);
}

// ========== Solution 2: 回溯 + 位掩码优化 ==========
// 思路：用 3 个 int[9] 数组分别记录每行/每列/每个九宫格已用的数字
//       每个数字用 1 位表示（bit 0~8 对应 '1'~'9'）
//       检查冲突从 O(9) 降为 O(1)（位运算）
// 时间复杂度: 最坏仍为 O(9^(81-k))，但常数大幅降低
// 空间复杂度: O(1) 额外空间（不计递归栈）
static bool backtrack2(vector<vector<char>>& board,
                       int rows[], int cols[], int boxes[]) {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] == '.') {
        int boxIdx = (i / 3) * 3 + (j / 3);
        // ~(rows|cols|boxes) & 0x1FF 得到可用数字的位掩码（低9位）
        int available = ~(rows[i] | cols[j] | boxes[boxIdx]) & 0x1FF;
        while (available) {
          // 取最低位的 1（数字最小优先尝试，也可优化顺序）
          int bit = available & -available;
          int digit = __builtin_ctz(bit);  // 0-indexed digit
          char c = '1' + digit;
          int mask = 1 << digit;

          board[i][j] = c;
          rows[i] |= mask;
          cols[j] |= mask;
          boxes[boxIdx] |= mask;

          if (backtrack2(board, rows, cols, boxes)) return true;

          // 回溯还原
          board[i][j] = '.';
          rows[i] &= ~mask;
          cols[j] &= ~mask;
          boxes[boxIdx] &= ~mask;

          available &= (available - 1);  // 清除最低位的 1
        }
        return false;
      }
    }
  }
  return true;
}

static void solution2(vector<vector<char>>& board) {
  int rows[9] = {0}, cols[9] = {0}, boxes[9] = {0};

  // 初始化位掩码：把已有的数字标记上
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] != '.') {
        int digit = board[i][j] - '1';
        int mask = 1 << digit;
        int boxIdx = (i / 3) * 3 + (j / 3);
        rows[i] |= mask;
        cols[j] |= mask;
        boxes[boxIdx] |= mask;
      }
    }
  }

  backtrack2(board, rows, cols, boxes);
}

// ========== Solution 3: 回溯 + 位掩码 + MRV 启发式 ==========
// 思路：在 solution2 基础上加入 MRV (Minimum Remaining Values) 启发式
//       每次选择候选数字最少的空格优先尝试，大幅减少搜索树分支
// 时间复杂度: 最坏同 O(9^(81-k))，实际运行提速数十倍
// 空间复杂度: O(1) 额外空间（不计递归栈）
static bool backtrack3(vector<vector<char>>& board,
                       int rows[], int cols[], int boxes[]) {
  // MRV：找候选数字最少的格子
  int minCandidates = 10;
  int bestRow = -1, bestCol = -1, bestAvail = 0;

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] == '.') {
        int boxIdx = (i / 3) * 3 + (j / 3);
        int available = ~(rows[i] | cols[j] | boxes[boxIdx]) & 0x1FF;
        int cnt = __builtin_popcount(available);
        if (cnt < minCandidates) {
          minCandidates = cnt;
          bestRow = i;
          bestCol = j;
          bestAvail = available;
          if (cnt == 1) goto try_best;  // 最优情况，直接跳出
        }
      }
    }
  }

try_best:
  if (bestRow == -1) return true;  // 全部填满

  int boxIdx = (bestRow / 3) * 3 + (bestCol / 3);
  while (bestAvail) {
    int bit = bestAvail & -bestAvail;
    int digit = __builtin_ctz(bit);
    char c = '1' + digit;
    int mask = 1 << digit;

    board[bestRow][bestCol] = c;
    rows[bestRow] |= mask;
    cols[bestCol] |= mask;
    boxes[boxIdx] |= mask;

    if (backtrack3(board, rows, cols, boxes)) return true;

    board[bestRow][bestCol] = '.';
    rows[bestRow] &= ~mask;
    cols[bestCol] &= ~mask;
    boxes[boxIdx] &= ~mask;

    bestAvail &= (bestAvail - 1);
  }

  return false;
}

static void solution3(vector<vector<char>>& board) {
  int rows[9] = {0}, cols[9] = {0}, boxes[9] = {0};

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      if (board[i][j] != '.') {
        int digit = board[i][j] - '1';
        int mask = 1 << digit;
        int boxIdx = (i / 3) * 3 + (j / 3);
        rows[i] |= mask;
        cols[j] |= mask;
        boxes[boxIdx] |= mask;
      }
    }
  }

  backtrack3(board, rows, cols, boxes);
}

// ========== 构造函数：注册元数据与策略 ==========
SudokuSolverSolution::SudokuSolverSolution() {
  setMetaInfo({.id = 37,
               .title = "Sudoku Solver",
               .url = "https://leetcode.com/problems/sudoku-solver/"});
  registerStrategy({.name = "Brute Force Backtracking"}, solution1);
  registerStrategy({.name = "Backtracking with Bitmask"}, solution2);
  registerStrategy({.name = "Backtracking with Bitmask + MRV"}, solution3);
}

// ========== 公开方法调度 ==========
void SudokuSolverSolution::solveSudoku(vector<vector<char>>& board) {
  return getSolution()(board);
}

}  // namespace problem_37
}  // namespace leetcode
