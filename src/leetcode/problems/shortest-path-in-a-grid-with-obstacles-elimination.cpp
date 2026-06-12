#include "leetcode/problems/shortest-path-in-a-grid-with-obstacles-elimination.h"

namespace leetcode {
namespace problem_1293 {

static int solution1(vector<vector<int>>& grid, int k) {
  int m = grid.size();
  int n = grid[0].size();
  
  // If k is large enough, we can directly go to the destination
  // Manhattan distance is the minimum steps
  if (k >= m + n - 2) {
    return m + n - 2;
  }
  
  // directions: up, down, left, right
  const vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  
  // visited[row][col][eliminated]: have we visited this state?
  vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(k + 1, false)));
  
  // BFS queue: (row, col, eliminated, steps)
  queue<tuple<int, int, int, int>> q;
  q.push({0, 0, 0, 0});
  visited[0][0][0] = true;
  
  while (!q.empty()) {
    auto [r, c, elim, steps] = q.front();
    q.pop();
    
    // Reached destination
    if (r == m - 1 && c == n - 1) {
      return steps;
    }
    
    for (auto [dr, dc] : dirs) {
      int nr = r + dr;
      int nc = c + dc;
      
      if (nr < 0 || nr >= m || nc < 0 || nc >= n) {
        continue;
      }
      
      if (grid[nr][nc] == 0) {
        // Empty cell, can move directly
        if (!visited[nr][nc][elim]) {
          visited[nr][nc][elim] = true;
          q.push({nr, nc, elim, steps + 1});
        }
      } else {
        // Obstacle, need to eliminate
        if (elim < k && !visited[nr][nc][elim + 1]) {
          visited[nr][nc][elim + 1] = true;
          q.push({nr, nc, elim + 1, steps + 1});
        }
      }
    }
  }
  
  return -1;
}

ShortestPathInAGridWithObstaclesEliminationSolution::ShortestPathInAGridWithObstaclesEliminationSolution() {
  setMetaInfo({
      .id = 1293,
      .title = "Shortest Path in a Grid with Obstacles Elimination",
      .url = "https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination"
  });
  registerStrategy({.name = "Brute Force"}, solution1);
}

int ShortestPathInAGridWithObstaclesEliminationSolution::shortestPath(vector<vector<int>>& grid, int k) {
  return getSolution()(grid, k);
}

}  // namespace problem_1293
}  // namespace leetcode
