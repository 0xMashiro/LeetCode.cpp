#include "leetcode/problems/cyclically-rotating-a-grid.h"

namespace leetcode {
namespace problem_1914 {

// 辅助函数：对单层进行旋转
static void rotateLayer(vector<vector<int>>& grid, int layer, int k) {
  int m = grid.size();
  int n = grid[0].size();
  
  // 当前层的边界
  int top = layer;
  int bottom = m - 1 - layer;
  int left = layer;
  int right = n - 1 - layer;
  
  // 提取该层所有元素（按顺时针顺序：上->右->下->左）
  vector<int> layerElements;
  
  // 上边：从左到右
  for (int col = left; col <= right; ++col) {
    layerElements.push_back(grid[top][col]);
  }
  // 右边：从上到下
  for (int row = top + 1; row <= bottom; ++row) {
    layerElements.push_back(grid[row][right]);
  }
  // 下边：从右到左
  if (bottom > top) {
    for (int col = right - 1; col >= left; --col) {
      layerElements.push_back(grid[bottom][col]);
    }
  }
  // 左边：从下到上
  if (right > left) {
    for (int row = bottom - 1; row > top; --row) {
      layerElements.push_back(grid[row][left]);
    }
  }
  
  int len = layerElements.size();
  if (len == 0) return;
  
  // 计算实际旋转次数
  k = k % len;
  if (k == 0) return;
  
  // 逆时针旋转 k 次：相当于数组向左循环移动 k 位
  // 原位置 (i + k) % len 的元素移动到位置 i
  vector<int> rotated(len);
  for (int i = 0; i < len; ++i) {
    int srcPos = (i + k) % len;  // 新位置 i 的元素来自原位置 srcPos
    rotated[i] = layerElements[srcPos];
  }
  
  // 将旋转后的元素填回矩阵（按顺时针顺序）
  int idx = 0;
  // 上边：从左到右
  for (int col = left; col <= right; ++col) {
    grid[top][col] = rotated[idx++];
  }
  // 右边：从上到下
  for (int row = top + 1; row <= bottom; ++row) {
    grid[row][right] = rotated[idx++];
  }
  // 下边：从右到左
  if (bottom > top) {
    for (int col = right - 1; col >= left; --col) {
      grid[bottom][col] = rotated[idx++];
    }
  }
  // 左边：从下到上
  if (right > left) {
    for (int row = bottom - 1; row > top; --row) {
      grid[row][left] = rotated[idx++];
    }
  }
}

// 主解法：对每一层进行 k 次循环旋转
static vector<vector<int>> solution(vector<vector<int>>& grid, int k) {
  int m = grid.size();
  int n = grid[0].size();
  
  // 层数 = min(m, n) / 2
  int layers = min(m, n) / 2;
  
  // 对每一层进行旋转
  for (int layer = 0; layer < layers; ++layer) {
    rotateLayer(grid, layer, k);
  }
  
  return grid;
}

CyclicallyRotatingAGridSolution::CyclicallyRotatingAGridSolution() {
  setMetaInfo({.id = 1914,
               .title = "Cyclically Rotating a Grid",
               .url = "https://leetcode.com/problems/cyclically-rotating-a-grid/"});
  registerStrategy("Layer by Layer", solution);
}

vector<vector<int>> CyclicallyRotatingAGridSolution::rotateGrid(vector<vector<int>>& grid, int k) {
  return getSolution()(grid, k);
}

}  // namespace problem_1914
}  // namespace leetcode
