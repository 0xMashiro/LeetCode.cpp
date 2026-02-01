#include "leetcode/problems/count-unguarded-cells-in-the-grid.h"

namespace leetcode {
namespace problem_2257 {

// 使用方向数组简化四个方向的遍历
static const int DIRS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 模拟标记法：先标记所有警卫和墙的位置，然后从每个警卫出发标记可见区域
// 时间复杂度: O(m*n + guards.length * (m+n)), 空间复杂度: O(m*n)
static int solution1(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
  // grid[i][j] = 0: 空单元格, 1: 警卫, 2: 墙, 3: 被保卫的单元格
  vector<vector<int>> grid(m, vector<int>(n, 0));
  
  // 标记警卫位置
  for (const auto& guard : guards) {
    grid[guard[0]][guard[1]] = 1;
  }
  
  // 标记墙位置
  for (const auto& wall : walls) {
    grid[wall[0]][wall[1]] = 2;
  }
  
  // 从每个警卫出发，标记四个方向的可见区域
  for (const auto& guard : guards) {
    int r = guard[0], c = guard[1];
    for (int d = 0; d < 4; ++d) {
      int nr = r + DIRS[d][0];
      int nc = c + DIRS[d][1];
      // 沿一个方向移动，直到越界或遇到墙/警卫
      while (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] != 1 && grid[nr][nc] != 2) {
        grid[nr][nc] = 3;  // 标记为被保卫
        nr += DIRS[d][0];
        nc += DIRS[d][1];
      }
    }
  }
  
  // 统计未被保卫的空单元格
  int unguarded = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 0) {
        ++unguarded;
      }
    }
  }
  
  return unguarded;
}

CountUnguardedCellsInTheGridSolution::CountUnguardedCellsInTheGridSolution() {
  setMetaInfo({.id = 2257,
               .title = "Count Unguarded Cells in the Grid",
               .url = "https://leetcode.com/problems/count-unguarded-cells-in-the-grid/"});
  registerStrategy("Simulation Marking", solution1);
}

int CountUnguardedCellsInTheGridSolution::countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
  return getSolution()(m, n, guards, walls);
}

}  // namespace problem_2257
}  // namespace leetcode
