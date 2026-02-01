
#include "leetcode/problems/search-a-2d-matrix-ii.h"

namespace leetcode {
namespace problem_240 {

/**
 * 从左下角开始搜索
 * 时间复杂度: O(m+n)，空间复杂度: O(1)
 * 
 * 思路：从左下角开始，matrix[row][col]
 * - 如果 matrix[row][col] == target: 找到目标，返回 true
 * - 如果 matrix[row][col] > target: 当前值太大，向上移动 row--
 * - 如果 matrix[row][col] < target: 当前值太小，向右移动 col++
 * 
 * 为什么从左下角或右上角开始？
 * 因为这些位置的元素具有"可排除性"：
 * - 左下角元素：右边都更大，上边都更小
 * - 所以每次比较可以排除一行或一列
 */
static bool solution1(vector<vector<int>>& matrix, int target) {
  if (matrix.empty() || matrix[0].empty()) {
    return false;
  }
  
  const int m = matrix.size();
  const int n = matrix[0].size();
  
  // 从左下角开始
  int row = m - 1;
  int col = 0;
  
  while (row >= 0 && col < n) {
    if (matrix[row][col] == target) {
      return true;
    } else if (matrix[row][col] > target) {
      // 当前值太大，向上移动（减小）
      row--;
    } else {
      // 当前值太小，向右移动（增大）
      col++;
    }
  }
  
  return false;
}

/**
 * 从右上角开始搜索（与左下角对称）
 * 时间复杂度: O(m+n)，空间复杂度: O(1)
 */
static bool solution2(vector<vector<int>>& matrix, int target) {
  if (matrix.empty() || matrix[0].empty()) {
    return false;
  }
  
  const int m = matrix.size();
  const int n = matrix[0].size();
  
  // 从右上角开始
  int row = 0;
  int col = n - 1;
  
  while (row < m && col >= 0) {
    if (matrix[row][col] == target) {
      return true;
    } else if (matrix[row][col] > target) {
      // 当前值太大，向左移动（减小）
      col--;
    } else {
      // 当前值太小，向下移动（增大）
      row++;
    }
  }
  
  return false;
}

SearchA2dMatrixIiSolution::SearchA2dMatrixIiSolution() {
  setMetaInfo({
    .id = 240,
    .title = "Search a 2D Matrix II",
    .url = "https://leetcode.com/problems/search-a-2d-matrix-ii/"
  });
  registerStrategy("Bottom-Left Start", solution1);
  registerStrategy("Top-Right Start", solution2);
}

bool SearchA2dMatrixIiSolution::searchMatrix(vector<vector<int>>& matrix, int target) {
  return getSolution()(matrix, target);
}

}  // namespace problem_240
}  // namespace leetcode
