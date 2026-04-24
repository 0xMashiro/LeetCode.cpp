#include "leetcode/problems/maximize-score-after-n-operations.h"

namespace leetcode {
namespace problem_1799 {

// DFS + 记忆化搜索（自顶向下）
// 从空状态开始，枚举所有未选数对，递归求解最大得分
// 时间复杂度: O(2^(2n) * n^2)，空间复杂度: O(2^n)
static int solution1(vector<int>& nums) {
  int m = nums.size();
  // 预处理所有数对的 gcd
  vector<vector<int>> gcds(m, vector<int>(m, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      int g = gcd(nums[i], nums[j]);
      gcds[i][j] = gcds[j][i] = g;
    }
  }

  vector<int> memo(1 << m, -1);

  function<int(int)> dfs = [&](int mask) -> int {
    if (mask == (1 << m) - 1) return 0;
    if (memo[mask] != -1) return memo[mask];

    int cnt = __builtin_popcount(mask);
    int op = cnt / 2 + 1;  // 当前是第几次操作（1-indexed）
    int res = 0;

    for (int i = 0; i < m; ++i) {
      if (mask & (1 << i)) continue;
      for (int j = i + 1; j < m; ++j) {
        if (mask & (1 << j)) continue;
        int newMask = mask | (1 << i) | (1 << j);
        res = max(res, op * gcds[i][j] + dfs(newMask));
      }
    }

    return memo[mask] = res;
  };

  return dfs(0);
}

// 迭代式 DP（自底向上）
// 从空状态开始，逐一向状态添加数对，递推最大得分
// 时间复杂度: O(2^(2n) * n^2)，空间复杂度: O(2^n)
static int solution2(vector<int>& nums) {
  int m = nums.size();
  // 预处理所有数对的 gcd
  vector<vector<int>> gcds(m, vector<int>(m, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      int g = gcd(nums[i], nums[j]);
      gcds[i][j] = gcds[j][i] = g;
    }
  }

  int total = 1 << m;
  vector<int> dp(total, 0);

  for (int mask = 0; mask < total; ++mask) {
    int cnt = __builtin_popcount(mask);
    if (cnt & 1) continue;  // 只处理偶数个已选元素的状态
    int op = cnt / 2;  // 已经完成了 op 次操作，接下来是第 op+1 次

    for (int i = 0; i < m; ++i) {
      if (mask & (1 << i)) continue;
      for (int j = i + 1; j < m; ++j) {
        if (mask & (1 << j)) continue;
        int newMask = mask | (1 << i) | (1 << j);
        dp[newMask] = max(dp[newMask], dp[mask] + (op + 1) * gcds[i][j]);
      }
    }
  }

  return dp[total - 1];
}

MaximizeScoreAfterNOperationsSolution::MaximizeScoreAfterNOperationsSolution() {
  setMetaInfo({.id = 1799,
               .title = "Maximize Score After N Operations",
               .url = "https://leetcode.com/problems/maximize-score-after-n-operations/"});
  registerStrategy("DFS + Memoization", solution1);
  registerStrategy("Iterative DP", solution2);
}

int MaximizeScoreAfterNOperationsSolution::maxScore(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1799
}  // namespace leetcode
