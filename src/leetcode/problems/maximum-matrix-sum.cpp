#include "leetcode/problems/maximum-matrix-sum.h"

namespace leetcode {
namespace problem_1975 {

// 核心思路：
// 1. 操作可以视为将负号在网格中移动，每次操作同时翻转两个相邻元素的符号
// 2. 如果矩阵中存在零，那么可以通过将负号移动到零上来消除所有负号
// 3. 如果负数的个数是偶数，可以两两配对消除，使所有元素非负
// 4. 否则，至少会留下一个负数，为了最大化总和，应让绝对值最小的元素为负
// 时间复杂度: O(n²), 空间复杂度: O(1)
static long long solution1(vector<vector<int>>& matrix) {
  const int n = matrix.size();
  long long sum_abs = 0;
  int negative_count = 0;
  int min_abs = INT_MAX;
  bool has_zero = false;
  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int val = matrix[i][j];
      int abs_val = abs(val);
      sum_abs += abs_val;
      if (val < 0) {
        ++negative_count;
      }
      if (val == 0) {
        has_zero = true;
      }
      if (abs_val < min_abs) {
        min_abs = abs_val;
      }
    }
  }
  
  // 如果存在零或者负数的个数是偶数，可以消除所有负号
  if (has_zero || negative_count % 2 == 0) {
    return sum_abs;
  }
  // 否则，需要留下一个负数，选择绝对值最小的元素为负
  return sum_abs - 2 * min_abs;
}

MaximumMatrixSumSolution::MaximumMatrixSumSolution() {
  setMetaInfo({.id = 1975,
               .title = "Maximum Matrix Sum",
               .url = "https://leetcode.com/problems/maximum-matrix-sum"});
  registerStrategy("Greedy", solution1);
}

long long MaximumMatrixSumSolution::maxMatrixSum(vector<vector<int>>& matrix) {
  return getSolution()(matrix);
}

}  // namespace problem_1975
}  // namespace leetcode