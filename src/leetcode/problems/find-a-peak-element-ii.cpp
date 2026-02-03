#include "leetcode/problems/find-a-peak-element-ii.h"

namespace leetcode {
namespace problem_1901 {

// 二分查找：对行进行二分，每次在中间行找到最大值，然后决定搜索方向
// 时间复杂度: O(m log n) -> 实际是 O(n log m)，因为每行找最大值是 O(n)
// 空间复杂度: O(1)
static vector<int> solution1(vector<vector<int>>& mat) {
  int m = mat.size();
  int n = mat[0].size();
  
  int top = 0, bottom = m - 1;
  
  while (top < bottom) {
    int mid = top + (bottom - top) / 2;
    
    // 在第 mid 行找到最大值的列索引
    int maxCol = 0;
    for (int j = 1; j < n; ++j) {
      if (mat[mid][j] > mat[mid][maxCol]) {
        maxCol = j;
      }
    }
    
    // 比较下方元素，决定搜索方向
    if (mat[mid][maxCol] < mat[mid + 1][maxCol]) {
      // 下方更大，去下半部分找
      top = mid + 1;
    } else {
      // 当前或上半部分有峰值
      bottom = mid;
    }
  }
  
  // 在最后一行找到最大值
  int maxCol = 0;
  for (int j = 1; j < n; ++j) {
    if (mat[top][j] > mat[top][maxCol]) {
      maxCol = j;
    }
  }
  
  return {top, maxCol};
}

// 另一种实现：对列进行二分，时间复杂度 O(m log n)
static vector<int> solution2(vector<vector<int>>& mat) {
  int m = mat.size();
  int n = mat[0].size();
  
  int left = 0, right = n - 1;
  
  while (left < right) {
    int mid = left + (right - left) / 2;
    
    // 在第 mid 列找到最大值的行索引
    int maxRow = 0;
    for (int i = 1; i < m; ++i) {
      if (mat[i][mid] > mat[maxRow][mid]) {
        maxRow = i;
      }
    }
    
    // 比较右侧元素，决定搜索方向
    if (mat[maxRow][mid] < mat[maxRow][mid + 1]) {
      // 右侧更大，去右半部分找
      left = mid + 1;
    } else {
      // 当前或左半部分有峰值
      right = mid;
    }
  }
  
  // 在最后一列找到最大值
  int maxRow = 0;
  for (int i = 1; i < m; ++i) {
    if (mat[i][left] > mat[maxRow][left]) {
      maxRow = i;
    }
  }
  
  return {maxRow, left};
}

FindAPeakElementIiSolution::FindAPeakElementIiSolution() {
  setMetaInfo({.id = 1901,
               .title = "Find a Peak Element II",
               .url = "https://leetcode.com/problems/find-a-peak-element-ii/"});
  registerStrategy("Binary Search on Rows", solution1);
  registerStrategy("Binary Search on Columns", solution2);
}

vector<int> FindAPeakElementIiSolution::findPeakGrid(vector<vector<int>>& mat) {
  return getSolution()(mat);
}

}  // namespace problem_1901
}  // namespace leetcode
