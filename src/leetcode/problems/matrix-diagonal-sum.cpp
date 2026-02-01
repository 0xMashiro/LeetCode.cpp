#include "leetcode/problems/matrix-diagonal-sum.h"

namespace leetcode {
namespace problem_1572 {

// 遍历主对角线和副对角线元素求和
// 主对角线：mat[i][i]
// 副对角线：mat[i][n-1-i]
// 如果 n 是奇数，中心元素会被重复计算，需要减去一次
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution(vector<vector<int>>& mat) {
  int n = mat.size();
  int sum = 0;
  
  for (int i = 0; i < n; ++i) {
    // 主对角线元素
    sum += mat[i][i];
    // 副对角线元素
    sum += mat[i][n - 1 - i];
  }
  
  // 如果 n 是奇数，中心元素被计算了两次，需要减去一次
  if (n % 2 == 1) {
    sum -= mat[n / 2][n / 2];
  }
  
  return sum;
}

MatrixDiagonalSumSolution::MatrixDiagonalSumSolution() {
  setMetaInfo({.id = 1572,
               .title = "Matrix Diagonal Sum",
               .url = "https://leetcode.com/problems/matrix-diagonal-sum/"});
  registerStrategy("Linear Scan", solution);
}

int MatrixDiagonalSumSolution::diagonalSum(vector<vector<int>>& mat) {
  return getSolution()(mat);
}

}  // namespace problem_1572
}  // namespace leetcode
