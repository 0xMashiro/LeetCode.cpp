#include "leetcode/problems/queens-that-can-attack-the-king.h"

namespace leetcode {
namespace problem_1222 {

/**
 * From king's position, search in 8 directions to find closest queens
 * Time Complexity: O(8 * 8) = O(1) - fixed board size
 * Space Complexity: O(1)
 */
static vector<vector<int>> solution1(vector<vector<int>>& queens, vector<int>& king) {
  // Mark all queen positions on the board
  bool board[8][8] = {};
  for (const auto& q : queens) {
    board[q[0]][q[1]] = true;
  }
  
  vector<vector<int>> result;
  
  // 8 directions: up, down, left, right, and 4 diagonals
  const int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
  const int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
  
  int kx = king[0], ky = king[1];
  
  // Search in each direction from king's position
  for (int dir = 0; dir < 8; ++dir) {
    int x = kx + dx[dir];
    int y = ky + dy[dir];
    
    // Move step by step in current direction
    while (x >= 0 && x < 8 && y >= 0 && y < 8) {
      if (board[x][y]) {
        // Found the closest queen in this direction
        result.push_back({x, y});
        break;  // Stop searching this direction
      }
      x += dx[dir];
      y += dy[dir];
    }
  }
  
  return result;
}

QueensThatCanAttackTheKingSolution::QueensThatCanAttackTheKingSolution() {
  setMetaInfo({
    .id = 1222,
    .title = "Queens That Can Attack the King",
    .url = "https://leetcode.com/problems/queens-that-can-attack-the-king/"
  });
  registerStrategy("8-Direction Search", solution1);
}

vector<vector<int>> QueensThatCanAttackTheKingSolution::queensAttacktheKing(
    vector<vector<int>>& queens, vector<int>& king) {
  return getSolution()(queens, king);
}

}  // namespace problem_1222
}  // namespace leetcode
