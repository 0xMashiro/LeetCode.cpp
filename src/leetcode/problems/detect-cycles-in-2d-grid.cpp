
#include "leetcode/problems/detect-cycles-in-2d-grid.h"

namespace leetcode {
namespace problem_1559 {

// DFS 检测环
// 时间复杂度: O(m*n), 空间复杂度: O(m*n)
static bool solution1(vector<vector<char>>& grid) {
  const int m = grid.size();
  const int n = grid[0].size();
  
  // visited[i][j] 表示该格子是否被访问过
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  
  // 方向数组：上、下、左、右
  const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  
  // DFS 函数：从 (r, c) 开始搜索，(parent_r, parent_c) 是父节点（来向）
  // 返回是否找到环
  function<bool(int, int, int, int)> dfs = [&](int r, int c, int parent_r, int parent_c) -> bool {
    visited[r][c] = true;
    
    for (const auto& dir : dirs) {
      int nr = r + dir[0];
      int nc = c + dir[1];
      
      // 检查边界
      if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
      // 值必须相同
      if (grid[nr][nc] != grid[r][c]) continue;
      // 不能回到父节点（避免立即返回）
      if (nr == parent_r && nc == parent_c) continue;
      
      if (visited[nr][nc]) {
        // 找到一个已访问的格子，且不是父节点，说明有环
        return true;
      }
      
      // 继续 DFS
      if (dfs(nr, nc, r, c)) {
        return true;
      }
    }
    
    return false;
  };
  
  // 从每个未访问的格子开始 DFS
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (!visited[i][j]) {
        if (dfs(i, j, -1, -1)) {
          return true;
        }
      }
    }
  }
  
  return false;
}

DetectCyclesIn2dGridSolution::DetectCyclesIn2dGridSolution() {
  setMetaInfo({.id = 1559,
               .title = "Detect Cycles in 2D Grid",
               .url = "https://leetcode.com/problems/detect-cycles-in-2d-grid/"});
  registerStrategy("DFS", solution1);
}

bool DetectCyclesIn2dGridSolution::containsCycle(vector<vector<char>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_1559
}  // namespace leetcode
