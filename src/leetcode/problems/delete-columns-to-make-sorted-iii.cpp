#include "leetcode/problems/delete-columns-to-make-sorted-iii.h"

namespace leetcode {
namespace problem_960 {

// 动态规划：最长满足条件的列子序列
// 时间复杂度: O(m^2 * n)，其中 m 是列数，n 是行数
// 空间复杂度: O(m)
static int solution1(vector<string>& strs) {
  int n = strs.size();           // 行数
  int m = strs[0].size();        // 列数
  
  // dp[i] 表示以第 i 列为结尾的最长满足条件的子序列长度
  vector<int> dp(m, 1);
  
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < j; ++i) {
      // 检查是否所有行都满足 strs[row][i] <= strs[row][j]
      bool valid = true;
      for (int row = 0; row < n; ++row) {
        if (strs[row][i] > strs[row][j]) {
          valid = false;
          break;
        }
      }
      if (valid) {
        dp[j] = max(dp[j], dp[i] + 1);
      }
    }
  }
  
  int max_len = *max_element(dp.begin(), dp.end());
  return m - max_len;
}

DeleteColumnsToMakeSortedIiiSolution::DeleteColumnsToMakeSortedIiiSolution() {
  setMetaInfo({.id = 960,
               .title = "Delete Columns to Make Sorted III",
               .url = "https://leetcode.com/problems/delete-columns-to-make-sorted-iii/"});
  registerStrategy("Dynamic Programming", solution1);
}

int DeleteColumnsToMakeSortedIiiSolution::minDeletionSize(vector<string>& strs) {
  return getSolution()(strs);
}

}  // namespace problem_960
}  // namespace leetcode