#include "leetcode/problems/equal-sum-grid-partition-i.h"

namespace leetcode {
namespace problem_3546 {

// 前缀和检查：计算总和，检查是否存在水平或垂直切割使两部分和相等
// 时间复杂度: O(m*n), 空间复杂度: O(1)
static bool solution1(vector<vector<int>> &grid) {
  const int m = grid.size();
  const int n = grid[0].size();

  // 计算总和
  long long total = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      total += grid[i][j];
    }
  }

  // 如果总和是奇数，无法平分
  if (total % 2 != 0) {
    return false;
  }

  long long target = total / 2;

  // 检查水平切割（在第 i 行后切，i 从 0 到 m-2）
  long long rowSum = 0;
  for (int i = 0; i < m - 1; ++i) {  // m-1 确保下面还有至少一行
    for (int j = 0; j < n; ++j) {
      rowSum += grid[i][j];
    }
    if (rowSum == target) {
      return true;
    }
  }

  // 检查垂直切割（在第 j 列后切，j 从 0 到 n-2）
  long long colSum = 0;
  for (int j = 0; j < n - 1; ++j) {  // n-1 确保右边还有至少一列
    for (int i = 0; i < m; ++i) {
      colSum += grid[i][j];
    }
    if (colSum == target) {
      return true;
    }
  }

  return false;
}

EqualSumGridPartitionISolution::EqualSumGridPartitionISolution() {
  setMetaInfo({.id = 3546,
               .title = "Equal Sum Grid Partition I",
               .url = "https://leetcode.com/problems/equal-sum-grid-partition-i/"});
  registerStrategy("Prefix Sum", solution1);
}

bool EqualSumGridPartitionISolution::canPartitionGrid(
    vector<vector<int>> &grid) {
  return getSolution()(grid);
}

}  // namespace problem_3546
}  // namespace leetcode
