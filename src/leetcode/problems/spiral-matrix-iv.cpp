#include "leetcode/problems/spiral-matrix-iv.h"

namespace leetcode {
namespace problem_2326 {

// 顺时针螺旋填充矩阵
// 时间复杂度: O(m * n), 空间复杂度: O(1)（除结果矩阵外）
static vector<vector<int>> solution1(int m, int n, ListNode* head) {
  // 创建 m x n 矩阵，初始化为 -1
  vector<vector<int>> matrix(m, vector<int>(n, -1));
  
  // 定义四个边界
  int top = 0, bottom = m - 1;
  int left = 0, right = n - 1;
  
  ListNode* cur = head;
  
  while (cur != nullptr && top <= bottom && left <= right) {
    // 从左到右填充 top 行
    for (int col = left; col <= right && cur != nullptr; ++col) {
      matrix[top][col] = cur->val;
      cur = cur->next;
    }
    ++top;
    
    // 从上到下填充 right 列
    for (int row = top; row <= bottom && cur != nullptr; ++row) {
      matrix[row][right] = cur->val;
      cur = cur->next;
    }
    --right;
    
    // 从右到左填充 bottom 行（需要检查 top <= bottom）
    if (top <= bottom) {
      for (int col = right; col >= left && cur != nullptr; --col) {
        matrix[bottom][col] = cur->val;
        cur = cur->next;
      }
      --bottom;
    }
    
    // 从下到上填充 left 列（需要检查 left <= right）
    if (left <= right) {
      for (int row = bottom; row >= top && cur != nullptr; --row) {
        matrix[row][left] = cur->val;
        cur = cur->next;
      }
      ++left;
    }
  }
  
  return matrix;
}

SpiralMatrixIvSolution::SpiralMatrixIvSolution() {
  setMetaInfo({.id = 2326,
               .title = "Spiral Matrix IV",
               .url = "https://leetcode.com/problems/spiral-matrix-iv/"});
  registerStrategy("Spiral Fill", solution1);
}

vector<vector<int>> SpiralMatrixIvSolution::spiralMatrix(int m, int n, ListNode* head) {
  return getSolution()(m, n, head);
}

}  // namespace problem_2326
}  // namespace leetcode
