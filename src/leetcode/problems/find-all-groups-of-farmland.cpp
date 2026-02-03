
#include "leetcode/problems/find-all-groups-of-farmland.h"

namespace leetcode {
namespace problem_1992 {

// 遍历矩阵，遇到 1 就找到对应的矩形区域
// 时间复杂度: O(m*n), 空间复杂度: O(1)（不包括结果）
static vector<vector<int>> solution1(vector<vector<int>>& land) {
  const int m = land.size();
  const int n = land[0].size();
  vector<vector<int>> result;
  
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      // 找到矩形的左上角 (必须是 1 且上方和左方都是 0 或者是边界)
      if (land[i][j] == 0) continue;
      if (i > 0 && land[i-1][j] == 1) continue;
      if (j > 0 && land[i][j-1] == 1) continue;
      
      // 找到矩形的右下角
      int r2 = i;
      int c2 = j;
      
      // 向下扩展找到最大行
      while (r2 + 1 < m && land[r2 + 1][j] == 1) {
        ++r2;
      }
      
      // 向右扩展找到最大列
      while (c2 + 1 < n && land[i][c2 + 1] == 1) {
        ++c2;
      }
      
      // 验证矩形内部是否全为 1（根据题意应该满足）
      // 添加结果
      result.push_back({i, j, r2, c2});
      
      // 将该矩形区域标记为 0（避免重复计算）
      for (int r = i; r <= r2; ++r) {
        for (int c = j; c <= c2; ++c) {
          land[r][c] = 0;
        }
      }
    }
  }
  
  return result;
}

// 优化版本：不需要在标记时遍历整个矩形，只需在遍历时跳过
static vector<vector<int>> solution2(vector<vector<int>>& land) {
  const int m = land.size();
  const int n = land[0].size();
  vector<vector<int>> result;
  
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (land[i][j] != 1) continue;
      
      // 找到矩形的右下角
      int r2 = i;
      int c2 = j;
      
      // 向下扩展找到最大行
      while (r2 + 1 < m && land[r2 + 1][j] == 1) {
        ++r2;
      }
      
      // 向右扩展找到最大列
      while (c2 + 1 < n && land[i][c2 + 1] == 1) {
        ++c2;
      }
      
      // 添加结果
      result.push_back({i, j, r2, c2});
      
      // 将该矩形区域标记为 0（避免重复计算）
      for (int r = i; r <= r2; ++r) {
        for (int c = j; c <= c2; ++c) {
          land[r][c] = 0;
        }
      }
    }
  }
  
  return result;
}

FindAllGroupsOfFarmlandSolution::FindAllGroupsOfFarmlandSolution() {
  setMetaInfo({.id = 1992,
               .title = "Find All Groups of Farmland",
               .url = "https://leetcode.com/problems/find-all-groups-of-farmland/"});
  registerStrategy("Optimized", solution2);
  registerStrategy("With Top-Left Check", solution1);
}

vector<vector<int>> FindAllGroupsOfFarmlandSolution::findFarmland(vector<vector<int>>& land) {
  return getSolution()(land);
}

}  // namespace problem_1992
}  // namespace leetcode
