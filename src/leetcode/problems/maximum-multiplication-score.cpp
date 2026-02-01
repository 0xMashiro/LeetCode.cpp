#include "leetcode/problems/maximum-multiplication-score.h"

namespace leetcode {
namespace problem_3290 {

// 动态规划：按顺序从 b 中选 4 个数与 a 相乘求最大得分
// dp[k] 表示已选 k+1 个数时的最大得分
// 时间复杂度: O(n), 空间复杂度: O(1)
static long long solution1(vector<int>& a, vector<int>& b) {
  const int n = b.size();
  // dp[0], dp[1], dp[2], dp[3] 分别对应选了 1, 2, 3, 4 个数时的最大得分
  // 初始化为极小值，表示尚未选够相应数量的数
  long long dp[4];
  dp[0] = dp[1] = dp[2] = dp[3] = LLONG_MIN;
  
  for (int i = 0; i < n; ++i) {
    // 倒序更新，避免重复选择同一个 b[i]
    // 尝试将 b[i] 作为第 4 个数
    if (dp[2] != LLONG_MIN) {
      dp[3] = max(dp[3], dp[2] + 1LL * a[3] * b[i]);
    }
    // 尝试将 b[i] 作为第 3 个数
    if (dp[1] != LLONG_MIN) {
      dp[2] = max(dp[2], dp[1] + 1LL * a[2] * b[i]);
    }
    // 尝试将 b[i] 作为第 2 个数
    if (dp[0] != LLONG_MIN) {
      dp[1] = max(dp[1], dp[0] + 1LL * a[1] * b[i]);
    }
    // 尝试将 b[i] 作为第 1 个数
    dp[0] = max(dp[0], 1LL * a[0] * b[i]);
  }
  
  return dp[3];
}

MaximumMultiplicationScoreSolution::MaximumMultiplicationScoreSolution() {
  setMetaInfo({.id = 3290,
               .title = "Maximum Multiplication Score",
               .url = "https://leetcode.com/problems/maximum-multiplication-score/"});
  registerStrategy("Dynamic Programming", solution1);
}

long long MaximumMultiplicationScoreSolution::maxScore(vector<int>& a, vector<int>& b) {
  return getSolution()(a, b);
}

}  // namespace problem_3290
}  // namespace leetcode
