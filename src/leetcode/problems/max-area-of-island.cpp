#include "leetcode/problems/max-area-of-island.h"

namespace leetcode {
namespace problem_695 {

// DFS 实现
// 时间复杂度: O(m * n)，每个单元格最多访问一次
// 空间复杂度: O(m * n)，递归栈深度
static int dfs(vector<vector<int>>& grid, int i, int j) {
  // 边界检查
  if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
    return 0;
  }
  // 如果是水或已访问过，返回 0
  if (grid[i][j] == 0) {
    return 0;
  }
  // 标记为已访问（沉岛法）
  grid[i][j] = 0;
  // 当前单元格贡献 1，加上四个方向的面积
  return 1 + dfs(grid, i + 1, j) + dfs(grid, i - 1, j) + 
             dfs(grid, i, j + 1) + dfs(grid, i, j - 1);
}

static int solution1(vector<vector<int>>& grid) {
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }
  
  int max_area = 0;
  const int m = grid.size();
  const int n = grid[0].size();
  
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 1) {
        max_area = max(max_area, dfs(grid, i, j));
      }
    }
  }
  
  return max_area;
}

MaxAreaOfIslandSolution::MaxAreaOfIslandSolution() {
  setMetaInfo({
    .id = 695,
    .title = "Max Area of Island",
    .url = "https://leetcode.com/problems/max-area-of-island/"
  });
  registerStrategy("DFS", solution1);
}

int MaxAreaOfIslandSolution::maxAreaOfIsland(vector<vector<int>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_695
}  // namespace leetcode
