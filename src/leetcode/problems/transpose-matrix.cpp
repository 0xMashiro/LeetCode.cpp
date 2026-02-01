#include "leetcode/problems/transpose-matrix.h"

namespace leetcode {
namespace problem_867 {

static vector<vector<int>> solution1(vector<vector<int>>& matrix) {
  const int m = matrix.size();
  const int n = matrix[0].size();
  
  vector<vector<int>> result(n, vector<int>(m));
  
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      result[j][i] = matrix[i][j];
    }
  }
  
  return result;
}

TransposeMatrixSolution::TransposeMatrixSolution() {
  setMetaInfo({.id = 867,
               .title = "Transpose Matrix",
               .url = "https://leetcode.com/problems/transpose-matrix/"});
  registerStrategy("Direct Transpose", solution1);
}

vector<vector<int>> TransposeMatrixSolution::transpose(vector<vector<int>>& matrix) {
  return getSolution()(matrix);
}

}  // namespace problem_867
}  // namespace leetcode