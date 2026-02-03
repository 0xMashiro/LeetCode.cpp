#include "leetcode/problems/longest-subsequence-with-decreasing-adjacent-difference.h"

namespace leetcode {
namespace problem_3409 {

// DP + 后缀最大值优化
// dp[v][d] 表示以值 v 结尾、最后一个差值为 d 的最长子序列长度
// 使用 last_suffix_max 避免重复值自我转移
static int solution(vector<int>& nums) {
  const int MAX_V = 305;
  
  // dp[v][d]：当前值 v 的最新 dp 状态
  vector<vector<int>> dp(MAX_V, vector<int>(MAX_V, 0));
  // suffix_max[v][d]：当前值 v 的后缀最大值
  vector<vector<int>> suffix_max(MAX_V, vector<int>(MAX_V, 0));
  // last_suffix_max[v]：值 v 上一次出现时的后缀最大值快照
  vector<vector<int>> last_suffix_max(MAX_V);
  vector<bool> has_seen(MAX_V, false);
  
  for (int x : nums) {
    vector<int> new_dp(MAX_V, 0);
    
    // 只从之前出现过的值转移（使用 last_suffix_max）
    for (int prev = 1; prev < MAX_V; ++prev) {
      if (!has_seen[prev]) continue;
      
      int d = abs(x - prev);
      int best = last_suffix_max[prev][d];
      
      if (best > 0) {
        new_dp[d] = max(new_dp[d], best + 1);
      } else {
        new_dp[d] = max(new_dp[d], 2);
      }
    }
    
    // 更新 dp[x]
    for (int d = 0; d < MAX_V; ++d) {
      dp[x][d] = max(dp[x][d], new_dp[d]);
    }
    
    // 重新计算 suffix_max[x]
    suffix_max[x][MAX_V - 1] = dp[x][MAX_V - 1];
    for (int d = MAX_V - 2; d >= 0; --d) {
      suffix_max[x][d] = max(suffix_max[x][d + 1], dp[x][d]);
    }
    
    // 保存当前 suffix_max[x] 作为下一次的转移来源
    last_suffix_max[x] = suffix_max[x];
    has_seen[x] = true;
  }
  
  int ans = 0;
  for (int v = 1; v < MAX_V; ++v) {
    if (has_seen[v]) {
      ans = max(ans, suffix_max[v][0]);
    }
  }
  
  return max(ans, 2);
}

LongestSubsequenceWithDecreasingAdjacentDifferenceSolution::LongestSubsequenceWithDecreasingAdjacentDifferenceSolution() {
  setMetaInfo({
    .id = 3409,
    .title = "Longest Subsequence With Decreasing Adjacent Difference",
    .url = "https://leetcode.com/problems/longest-subsequence-with-decreasing-adjacent-difference/"
  });
  registerStrategy("DP Optimized", solution);
}

int LongestSubsequenceWithDecreasingAdjacentDifferenceSolution::longestSubsequence(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3409
}  // namespace leetcode
