#include "leetcode/problems/shift-2d-grid.h"

namespace leetcode {
namespace problem_1260 {

// 核心算法：将二维网格视为一维数组，计算每个元素的新位置
// 位置 (i, j) 对应一维索引 idx = i * n + j
// 平移 k 次后，新位置为 (idx + k) % total
static vector<vector<int>> shiftGridImpl(vector<vector<int>>& grid, int k) {
  int m = grid.size();
  int n = grid[0].size();
  int total = m * n;
  
  // k 可能很大，取模避免无效循环
  k = k % total;
  if (k == 0) return grid;
  
  vector<vector<int>> result(m, vector<int>(n));
  
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      int oldIdx = i * n + j;
      int newIdx = (oldIdx + k) % total;
      int newI = newIdx / n;
      int newJ = newIdx % n;
      result[newI][newJ] = grid[i][j];
    }
  }
  
  return result;
}

vector<vector<int>> Shift2dGridSolution::shiftGrid(vector<vector<int>>& grid, int k) {
  return shiftGridImpl(grid, k);
}

Shift2dGridSolution::Shift2dGridSolution() {
  setMetaInfo({.id = 1260,
               .title = "Shift 2D Grid",
               .url = "https://leetcode.com/problems/shift-2d-grid/"});
  registerStrategy("1D Conversion", shiftGridImpl);
}

}  // namespace problem_1260
}  // namespace leetcode
