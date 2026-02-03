#include "leetcode/problems/find-a-safe-walk-through-a-grid.h"

namespace leetcode {
namespace problem_3286 {

// BFS 求经过1最少的路径
// 使用优先队列（最小堆），优先扩展经过1少的节点
// 时间复杂度: O(m*n*log(m*n)), 空间复杂度: O(m*n)
static bool solution1(vector<vector<int>>& grid, int health) {
  const int m = grid.size();
  const int n = grid[0].size();
  
  // 优先队列: {当前经过的1的数量, x, y}
  // 使用 greater 使堆顶是经过1最少的
  using State = tuple<int, int, int>;
  priority_queue<State, vector<State>, greater<State>> pq;
  
  // dist[i][j] 表示到达 (i,j) 最少需要经过多少个1
  vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
  
  // 起点消耗
  int startCost = grid[0][0];
  dist[0][0] = startCost;
  pq.push({startCost, 0, 0});
  
  const int dx[] = {-1, 1, 0, 0};
  const int dy[] = {0, 0, -1, 1};
  
  while (!pq.empty()) {
    auto [cost, x, y] = pq.top();
    pq.pop();
    
    // 到达终点
    if (x == m - 1 && y == n - 1) {
      return health - cost >= 1;
    }
    
    // 已经找到更优路径
    if (cost > dist[x][y]) continue;
    
    for (int i = 0; i < 4; ++i) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      
      if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
      
      int newCost = cost + grid[nx][ny];
      if (newCost < dist[nx][ny]) {
        dist[nx][ny] = newCost;
        pq.push({newCost, nx, ny});
      }
    }
  }
  
  // 无法到达终点
  return false;
}

FindASafeWalkThroughAGridSolution::FindASafeWalkThroughAGridSolution() {
  setMetaInfo({.id = 3286,
               .title = "Find a Safe Walk Through a Grid",
               .url = "https://leetcode.com/problems/find-a-safe-walk-through-a-grid/"});
  registerStrategy("Dijkstra", solution1);
}

bool FindASafeWalkThroughAGridSolution::findSafeWalk(vector<vector<int>>& grid, int health) {
  return getSolution()(grid, health);
}

}  // namespace problem_3286
}  // namespace leetcode
