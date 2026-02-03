
#include "leetcode/problems/available-captures-for-rook.h"

namespace leetcode {
namespace problem_999 {

// 先找到车的位置，然后向四个方向扫描
// 时间复杂度: O(64) = O(1), 空间复杂度: O(1)
static int solution1(vector<vector<char>>& board) {
  // 找到车的位置
  int rookRow = -1, rookCol = -1;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (board[i][j] == 'R') {
        rookRow = i;
        rookCol = j;
        break;
      }
    }
    if (rookRow != -1) break;
  }
  
  int count = 0;
  // 四个方向: 上、下、左、右
  int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  
  for (int d = 0; d < 4; ++d) {
    int dr = directions[d][0];
    int dc = directions[d][1];
    int r = rookRow + dr;
    int c = rookCol + dc;
    
    // 向该方向一直走，直到出界或遇到棋子
    while (r >= 0 && r < 8 && c >= 0 && c < 8) {
      if (board[r][c] != '.') {
        // 遇到第一个棋子
        if (board[r][c] == 'p') {
          count++;  // 是黑兵，可以攻击
        }
        break;  // 无论是什么棋子，都停止这个方向的扫描
      }
      r += dr;
      c += dc;
    }
  }
  
  return count;
}

AvailableCapturesForRookSolution::AvailableCapturesForRookSolution() {
  setMetaInfo({.id = 999,
               .title = "Available Captures for Rook",
               .url = "https://leetcode.com/problems/available-captures-for-rook/"});
  registerStrategy("Linear Scan", solution1);
}

int AvailableCapturesForRookSolution::numRookCaptures(vector<vector<char>>& board) {
  return getSolution()(board);
}

}  // namespace problem_999
}  // namespace leetcode
