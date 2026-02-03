
#include "leetcode/problems/nearest-exit-from-entrance-in-maze.h"

namespace leetcode {
namespace problem_1926 {

/**
 * BFS 最短路径算法
 * 时间复杂度: O(m * n)，每个格子最多访问一次
 * 空间复杂度: O(m * n)，visited 数组和队列
 */
static int solution1(vector<vector<char>>& maze, vector<int>& entrance) {
  int m = maze.size();
  int n = maze[0].size();
  
  // 记录起始位置
  int startRow = entrance[0];
  int startCol = entrance[1];
  
  // 方向数组：上、下、左、右
  const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  
  // BFS 队列，存储 (row, col, steps)
  queue<tuple<int, int, int>> q;
  q.push({startRow, startCol, 0});
  
  // visited 数组，标记已访问位置
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  visited[startRow][startCol] = true;
  
  while (!q.empty()) {
    auto [row, col, steps] = q.front();
    q.pop();
    
    // 向四个方向扩展
    for (const auto& [dr, dc] : directions) {
      int newRow = row + dr;
      int newCol = col + dc;
      
      // 检查边界
      if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n) {
        continue;
      }
      
      // 检查是否是墙壁
      if (maze[newRow][newCol] == '+') {
        continue;
      }
      
      // 检查是否已访问
      if (visited[newRow][newCol]) {
        continue;
      }
      
      // 标记为已访问
      visited[newRow][newCol] = true;
      
      // 检查是否是出口（在边界上且不是 entrance）
      if (newRow == 0 || newRow == m - 1 || newCol == 0 || newCol == n - 1) {
        return steps + 1;
      }
      
      // 加入队列继续搜索
      q.push({newRow, newCol, steps + 1});
    }
  }
  
  // 无法到达任何出口
  return -1;
}

NearestExitFromEntranceInMazeSolution::NearestExitFromEntranceInMazeSolution() {
  setMetaInfo({.id = 1926,
               .title = "Nearest Exit from Entrance in Maze",
               .url = "https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/"});
  registerStrategy("BFS", solution1);
}

int NearestExitFromEntranceInMazeSolution::nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
  return getSolution()(maze, entrance);
}

}  // namespace problem_1926
}  // namespace leetcode
