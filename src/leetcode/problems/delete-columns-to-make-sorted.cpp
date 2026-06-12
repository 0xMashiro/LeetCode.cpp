#include "leetcode/problems/delete-columns-to-make-sorted.h"

namespace leetcode {
namespace problem_944 {

// 逐列检查：对每一列，检查所有行是否按字典序非递减排列
// 时间复杂度: O(n * m)，其中 n 是字符串数量，m 是字符串长度
// 空间复杂度: O(1)
static int solution1(vector<string>& strs) {
  int n = strs.size();
  if (n == 0) return 0;
  int m = strs[0].size();
  int count = 0;
  
  for (int col = 0; col < m; ++col) {
    for (int row = 1; row < n; ++row) {
      if (strs[row][col] < strs[row - 1][col]) {
        ++count;
        break;
      }
    }
  }
  return count;
}

DeleteColumnsToMakeSortedSolution::DeleteColumnsToMakeSortedSolution() {
  setMetaInfo({.id = 944,
               .title = "Delete Columns to Make Sorted",
               .url = "https://leetcode.com/problems/delete-columns-to-make-sorted/"});
  registerStrategy({.name = "Column-wise Check"}, solution1);
}

int DeleteColumnsToMakeSortedSolution::minDeletionSize(vector<string>& strs) {
  return getSolution()(strs);
}

}  // namespace problem_944
}  // namespace leetcode