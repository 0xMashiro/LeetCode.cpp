#include "leetcode/problems/kth-smallest-element-in-a-sorted-matrix.h"

namespace leetcode {
namespace problem_378 {

// 二分查找解法
// 时间复杂度: O(n log(max-min)), 空间复杂度: O(1)
// 思路：对值域进行二分，统计矩阵中 <= mid 的元素个数
static int solution1(vector<vector<int>>& matrix, int k) {
  const int n = matrix.size();
  int left = matrix[0][0];
  int right = matrix[n - 1][n - 1];

  while (left < right) {
    int mid = left + (right - left) / 2;

    // 统计矩阵中 <= mid 的元素个数
    // 从左下角开始，利用行列有序性
    int count = 0;
    int row = n - 1;  // 从最后一行开始
    int col = 0;      // 从第一列开始

    while (row >= 0 && col < n) {
      if (matrix[row][col] <= mid) {
        // 当前元素 <= mid，则当前元素上方的所有元素都 <= mid
        count += row + 1;
        col++;  // 向右移动
      } else {
        // 当前元素 > mid，向上移动
        row--;
      }
    }

    if (count < k) {
      // 第 k 小的数在右半部分
      left = mid + 1;
    } else {
      // 第 k 小的数在左半部分（包含 mid）
      right = mid;
    }
  }

  return left;
}

KthSmallestElementInASortedMatrixSolution::KthSmallestElementInASortedMatrixSolution() {
  setMetaInfo({.id = 378,
               .title = "Kth Smallest Element in a Sorted Matrix",
               .url = "https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/"});
  registerStrategy("Binary Search", solution1);
}

int KthSmallestElementInASortedMatrixSolution::kthSmallest(vector<vector<int>>& matrix, int k) {
  return getSolution()(matrix, k);
}

}  // namespace problem_378
}  // namespace leetcode
