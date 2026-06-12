#include "leetcode/problems/jump-game-v.h"

namespace leetcode {
namespace problem_1340 {

// ========== 方案 1：记忆化搜索（DFS + Memo） ==========
// 从每个位置 i 出发，递归尝试向左/向右跳最多 d 步
// 只有当 arr[j] < arr[i] 且中间所有值 < arr[i] 时才能跳
// 时间复杂度: O(n * d)，空间复杂度: O(n)
static int solution1(vector<int>& arr, int d) {
  const int n = arr.size();
  vector<int> memo(n, -1);

  function<int(int)> dfs = [&](int i) -> int {
    if (memo[i] != -1) return memo[i];
    int best = 1;  // 至少可以访问自己

    // 向右跳
    for (int x = 1; x <= d && i + x < n; ++x) {
      if (arr[i + x] >= arr[i]) break;  // 中间有 >= 当前值的障碍，不能再远了
      best = max(best, 1 + dfs(i + x));
    }

    // 向左跳
    for (int x = 1; x <= d && i - x >= 0; ++x) {
      if (arr[i - x] >= arr[i]) break;  // 中间有 >= 当前值的障碍，不能再远了
      best = max(best, 1 + dfs(i - x));
    }

    memo[i] = best;
    return best;
  };

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = max(ans, dfs(i));
  }
  return ans;
}

// ========== 方案 2：排序 + DP（Bottom-up） ==========
// 按 arr[i] 升序排序索引，从小到大处理
// 当处理到位置 i 时，所有比 arr[i] 低的位置都已经被算好了
// 时间复杂度: O(n log n + n * d)，空间复杂度: O(n)
static int solution2(vector<int>& arr, int d) {
  const int n = arr.size();
  // 按值升序排序索引
  vector<int> indices(n);
  iota(indices.begin(), indices.end(), 0);
  sort(indices.begin(), indices.end(),
       [&](int a, int b) { return arr[a] < arr[b]; });

  vector<int> dp(n, 1);  // 每个位置至少能访问自己

  for (int idx : indices) {
    // 向右跳
    for (int x = 1; x <= d && idx + x < n; ++x) {
      if (arr[idx + x] >= arr[idx]) break;
      dp[idx] = max(dp[idx], 1 + dp[idx + x]);
    }
    // 向左跳
    for (int x = 1; x <= d && idx - x >= 0; ++x) {
      if (arr[idx - x] >= arr[idx]) break;
      dp[idx] = max(dp[idx], 1 + dp[idx - x]);
    }
  }

  return *max_element(dp.begin(), dp.end());
}

JumpGameVSolution::JumpGameVSolution() {
  setMetaInfo({.id = 1340,
               .title = "Jump Game V",
               .url = "https://leetcode.com/problems/jump-game-v/"});
  registerStrategy({.name = "Memoization DFS"}, solution1);
  registerStrategy({.name = "Sort + DP"}, solution2);
}

int JumpGameVSolution::maxJumps(vector<int>& arr, int d) {
  return getSolution()(arr, d);
}

}  // namespace problem_1340
}  // namespace leetcode
