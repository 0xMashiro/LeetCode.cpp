#include "leetcode/problems/count-negative-numbers-in-a-sorted-matrix.h"

namespace leetcode {
namespace problem_1351 {

// 暴力遍历：遍历所有元素
// 时间复杂度: O(m*n), 空间复杂度: O(1)
static int solution1(vector<vector<int>>& grid) {
  int count = 0;
  for (const auto& row : grid) {
    for (int x : row) {
      if (x < 0) ++count;
    }
  }
  return count;
}

// 逐行二分查找：对每一行进行二分查找，找到第一个负数的位置
// 时间复杂度: O(m log n), 空间复杂度: O(1)
static int solution2(vector<vector<int>>& grid) {
  int total = 0;
  for (const auto& row : grid) {
    // 由于每行是非递增的，使用二分查找找到第一个负数的位置
    int left = 0, right = row.size();
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (row[mid] < 0) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    total += row.size() - left;
  }
  return total;
}

// 从右上角搜索：利用行列都是非递增的性质
// 时间复杂度: O(m + n), 空间复杂度: O(1)
static int solution3(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  int row = 0, col = n - 1;
  int count = 0;
  while (row < m && col >= 0) {
    if (grid[row][col] < 0) {
      // 当前列 col 在 row 行及以下的所有行都是负数（列非递增）
      count += (m - row);
      --col;  // 这一列已经全部统计完，向左移动
    } else {
      // 当前行 row 的 col 列及左边的元素都 >=0（行非递增）
      ++row;  // 进入下一行
    }
  }
  return count;
}

// 从左下角搜索：同样利用行列非递增的性质
// 时间复杂度: O(m + n), 空间复杂度: O(1)
static int solution4(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  int row = m - 1, col = 0;
  int count = 0;
  while (row >= 0 && col < n) {
    if (grid[row][col] < 0) {
      // 当前行 row 的 col 列及右侧的所有列都是负数（行非递增）
      count += (n - col);
      --row;  // 这一行已经全部统计完，向上移动
    } else {
      // 当前列 col 在 row 行及以上的所有行都 >=0（列非递增）
      ++col;  // 向右移动
    }
  }
  return count;
}

CountNegativeNumbersInASortedMatrixSolution::CountNegativeNumbersInASortedMatrixSolution() {
  setMetaInfo({.id = 1351,
               .title = "Count Negative Numbers in a Sorted Matrix",
               .url = "https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Binary Search per Row", solution2);
  registerStrategy("Search from Top-Right", solution3);
  registerStrategy("Search from Bottom-Left", solution4);
}

int CountNegativeNumbersInASortedMatrixSolution::countNegatives(vector<vector<int>>& grid) {
  return getSolution()(grid);
}

}  // namespace problem_1351
}  // namespace leetcode