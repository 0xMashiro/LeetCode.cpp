#include "leetcode/problems/rotate-image.h"

namespace leetcode {
namespace problem_48 {

// 转置 + 行反转：先沿主对角线转置，再反转每一行
// 时间复杂度: O(n^2), 空间复杂度: O(1)
static void solution1(vector<vector<int>>& matrix) {
  int n = matrix.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      swap(matrix[i][j], matrix[j][i]);
    }
  }
  for (int i = 0; i < n; ++i) {
    reverse(matrix[i].begin(), matrix[i].end());
  }
}

// 逐层四向旋转：按同心正方形层处理，每层 4 元素循环交换
// 时间复杂度: O(n^2), 空间复杂度: O(1)
static void solution2(vector<vector<int>>& matrix) {
  int n = matrix.size();
  for (int i = 0; i < n / 2; ++i) {
    for (int j = i; j < n - 1 - i; ++j) {
      int temp = matrix[i][j];
      matrix[i][j] = matrix[n - 1 - j][i];
      matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
      matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
      matrix[j][n - 1 - i] = temp;
    }
  }
}

RotateImageSolution::RotateImageSolution() {
  setMetaInfo({.id = 48,
               .title = "Rotate Image",
               .url = "https://leetcode.com/problems/rotate-image/"});
  registerStrategy({.name = "Transpose + Reverse"}, solution1);
  registerStrategy({.name = "Layer Rotation"}, solution2);
}

void RotateImageSolution::rotate(vector<vector<int>>& matrix) {
  return getSolution()(matrix);
}

}  // namespace problem_48
}  // namespace leetcode
