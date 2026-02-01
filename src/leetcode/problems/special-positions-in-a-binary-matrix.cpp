
#include "leetcode/problems/special-positions-in-a-binary-matrix.h"

namespace leetcode {
namespace problem_1582 {

// 预处理：先统计每行每列的 1 的数量，再遍历判断
// 时间复杂度: O(m * n), 空间复杂度: O(m + n)
static int solution1(vector<vector<int>>& mat) {
  const int m = mat.size();
  const int n = mat[0].size();
  
  vector<int> rowSum(m, 0);
  vector<int> colSum(n, 0);
  
  // 统计每行每列的 1 的数量
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mat[i][j] == 1) {
        rowSum[i]++;
        colSum[j]++;
      }
    }
  }
  
  // 统计特殊位置数量
  int result = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mat[i][j] == 1 && rowSum[i] == 1 && colSum[j] == 1) {
        result++;
      }
    }
  }
  
  return result;
}

SpecialPositionsInABinaryMatrixSolution::SpecialPositionsInABinaryMatrixSolution() {
  setMetaInfo({.id = 1582,
               .title = "Special Positions in a Binary Matrix",
               .url = "https://leetcode.com/problems/special-positions-in-a-binary-matrix/"});
  registerStrategy("Preprocessing", solution1);
}

int SpecialPositionsInABinaryMatrixSolution::numSpecial(vector<vector<int>>& mat) {
  return getSolution()(mat);
}

}  // namespace problem_1582
}  // namespace leetcode
