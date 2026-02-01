#include "leetcode/problems/check-if-there-is-a-valid-path-in-a-grid.h"

namespace leetcode {
namespace problem_1391 {

/**
 * 检查两个相邻街道是否连通
 * 
 * 每个街道有4个方向的开孔（上右下左，用位表示）：
 * 类型1 (左右): 0b1010 (左+右)
 * 类型2 (上下): 0b0101 (上+下)
 * 类型3 (左下): 0b0011 (左+下)
 * 类型4 (右下): 0b0110 (右+下)
 * 类型5 (左上): 0b1001 (左+上)
 * 类型6 (右上): 0b1100 (右+上)
 */

// 每个街道类型的开孔情况（上、右、下、左）用位掩码表示
// bit 0: 上, bit 1: 右, bit 2: 下, bit 3: 左
// 位定义: bit 0=上, bit 1=右, bit 2=下, bit 3=左
const int STREET_MASK[7] = {
  0,        // 占位
  0b1010,   // 类型1: 左右 (左+右) -> bit 3 + bit 1
  0b0101,   // 类型2: 上下 (上+下) -> bit 0 + bit 2
  0b1100,   // 类型3: 左下 (左+下) -> bit 3 + bit 2
  0b0110,   // 类型4: 右下 (右+下) -> bit 1 + bit 2
  0b1001,   // 类型5: 左上 (左+上) -> bit 3 + bit 0
  0b0011    // 类型6: 右上 (右+上) -> bit 1 + bit 0
};

// 方向的反方向（上<->下, 左<->右）
// 上(0)<->下(2), 右(1)<->左(3)
const int OPPOSITE[4] = {2, 3, 0, 1};

// 方向的坐标变化: 上, 右, 下, 左
const int DX[4] = {-1, 0, 1, 0};
const int DY[4] = {0, 1, 0, -1};

/**
 * 检查从 (x,y) 能否走向 (nx,ny)
 * 需要满足：
 * 1. 当前格子有出口指向相邻格子
 * 2. 相邻格子有入口接收（即相邻格子有出口指向当前格子）
 */
static bool canConnect(const vector<vector<int>>& grid, int x, int y, int dir) {
  int m = grid.size();
  int n = grid[0].size();
  
  int nx = x + DX[dir];
  int ny = y + DY[dir];
  
  // 边界检查
  if (nx < 0 || nx >= m || ny < 0 || ny >= n) return false;
  
  int currType = grid[x][y];
  int nextType = grid[nx][ny];
  
  // 当前格子在 dir 方向有开孔，且相邻格子在反方向有开孔
  return (STREET_MASK[currType] >> dir) & 1 && 
         (STREET_MASK[nextType] >> OPPOSITE[dir]) & 1;
}

/**
 * BFS 解法
 */
static bool solution1(vector<vector<int>>& grid) {
  if (grid.empty() || grid[0].empty()) return false;
  
  const int m = grid.size();
  const int n = grid[0].size();
  
  // 如果起点就是终点
  if (m == 1 && n == 1) return true;
  
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  queue<pair<int, int>> q;
  
  q.push({0, 0});
  visited[0][0] = true;
  
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    
    // 尝试4个方向
    for (int dir = 0; dir < 4; dir++) {
      if (!canConnect(grid, x, y, dir)) continue;
      
      int nx = x + DX[dir];
      int ny = y + DY[dir];
      
      if (visited[nx][ny]) continue;
      
      // 到达终点
      if (nx == m - 1 && ny == n - 1) return true;
      
      visited[nx][ny] = true;
      q.push({nx, ny});
    }
  }
  
  return false;
}

/**
 * DFS 解法
 */
static bool solution2(vector<vector<int>>& grid) {
  if (grid.empty() || grid[0].empty()) return false;
  
  const int m = grid.size();
  const int n = grid[0].size();
  
  if (m == 1 && n == 1) return true;
  
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  
  function<bool(int, int)> dfs = [&](int x, int y) -> bool {
    if (x == m - 1 && y == n - 1) return true;
    
    visited[x][y] = true;
    
    for (int dir = 0; dir < 4; dir++) {
      if (!canConnect(grid, x, y, dir)) continue;
      
      int nx = x + DX[dir];
      int ny = y + DY[dir];
      
      if (visited[nx][ny]) continue;
      
      if (dfs(nx, ny)) return true;
    }
    
    return false;
  };
  
  return dfs(0, 0);
}

CheckIfThereIsAValidPathInAGridSolution::CheckIfThereIsAValidPathInAGridSolution() {
  setMetaInfo({
    .id = 1391,
    .title = "Check if There is a Valid Path in a Grid",
    .url = "https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/"
  });
  registerStrategy("BFS", solution1);
  registerStrategy("DFS", solution2);
}

bool CheckIfThereIsAValidPathInAGridSolution::hasValidPath(vector<vector<int>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_1391
}  // namespace leetcode
