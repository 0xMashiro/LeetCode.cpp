#include "leetcode/problems/matrix-block-sum.h"

namespace leetcode {
namespace problem_1314 {

/**
 * 二维前缀和优化解法
 * 时间复杂度: O(m*n)
 * 空间复杂度: O(m*n)
 *
 * 思路：
 * 1. 构建二维前缀和数组 prefix，prefix[i][j] 表示从 (0,0) 到 (i-1,j-1) 的子矩阵和
 *    prefix[i][j] = mat[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
 *
 * 2. 对于 answer[i][j]，计算其对应的矩形边界：
 *    r1 = max(0, i - k), c1 = max(0, j - k)
 *    r2 = min(m-1, i + k), c2 = min(n-1, j + k)
 *
 * 3. 用前缀和计算矩形区域和：
 *    sum(r1..r2, c1..c2) = prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1]
 */
static vector<vector<int>> solution1(vector<vector<int>>& mat, int k) {
  const int m = mat.size();
  const int n = mat[0].size();

  // 构建二维前缀和数组 (m+1) x (n+1)
  vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      prefix[i][j] = mat[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] -
                     prefix[i - 1][j - 1];
    }
  }

  // 计算答案矩阵
  vector<vector<int>> answer(m, vector<int>(n, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      // 计算有效矩形边界
      int r1 = max(0, i - k);
      int c1 = max(0, j - k);
      int r2 = min(m - 1, i + k);
      int c2 = min(n - 1, j + k);

      // 用前缀和计算区域和（注意 prefix 数组索引要 +1）
      answer[i][j] = prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1] -
                     prefix[r2 + 1][c1] + prefix[r1][c1];
    }
  }

  return answer;
}

MatrixBlockSumSolution::MatrixBlockSumSolution() {
  setMetaInfo({.id = 1314,
               .title = "Matrix Block Sum",
               .url = "https://leetcode.com/problems/matrix-block-sum/"});
  registerStrategy("2D Prefix Sum", solution1);
}

vector<vector<int>> MatrixBlockSumSolution::matrixBlockSum(
    vector<vector<int>>& mat, int k) {
  return getSolution()(mat, k);
}

}  // namespace problem_1314
}  // namespace leetcode
