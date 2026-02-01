#include "leetcode/problems/new-21-game.h"

namespace leetcode {
namespace problem_837 {

/**
 * 动态规划 + 滑动窗口优化
 * 
 * 思路：
 * - dp[i] 表示当前分数为 i 时，最终分数 <= n 的概率
 * - 当 i >= k 时停止抽卡：若 i <= n 则 dp[i] = 1，否则 dp[i] = 0
 * - 当 i < k 时继续抽卡：dp[i] = sum(dp[i+j]) / maxPts, j in [1, maxPts]
 * 
 * 滑动窗口优化：
 * - 维护窗口和 windowSum = dp[i+1] + dp[i+2] + ... + dp[i+maxPts]
 * - 每次计算 dp[i] = windowSum / maxPts
 * - 更新 windowSum = windowSum + dp[i+1] - dp[i+maxPts+1]
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
static double solution1(int n, int k, int maxPts) {
  // 边界情况：不需要抽卡
  if (k == 0) return 1.0;
  
  // 如果最大可能分数 k-1+maxPts <= n，则概率为 1
  if (n >= k - 1 + maxPts) return 1.0;
  
  // dp[i] 表示当前分数为 i 时，最终分数 <= n 的概率
  vector<double> dp(n + 1, 0.0);
  
  // 初始化：i >= k 时的值
  // 当 k <= i <= n 时，dp[i] = 1
  for (int i = k; i <= n; ++i) {
    dp[i] = 1.0;
  }
  
  // 计算 dp[k-1]
  // dp[k-1] = (dp[k] + dp[k+1] + ... + dp[k-1+maxPts]) / maxPts
  // 其中 dp[k] 到 dp[n] 都是 1，dp[n+1] 到 dp[k-1+maxPts] 是 0（超出范围或大于n）
  double windowSum = 0.0;
  for (int i = k; i <= min(n, k - 1 + maxPts); ++i) {
    windowSum += dp[i];
  }
  dp[k - 1] = windowSum / maxPts;
  
  // 使用滑动窗口计算 dp[k-2] 到 dp[0]
  for (int i = k - 2; i >= 0; --i) {
    // 从右向左滑动：窗口原来是 [i+2, i+maxPts+1]，现在变成 [i+1, i+maxPts]
    // 左边加入 dp[i+1]，右边移除 dp[i+maxPts+1]
    windowSum += dp[i + 1];
    if (i + 1 + maxPts <= n) {
      windowSum -= dp[i + 1 + maxPts];
    }
    dp[i] = windowSum / maxPts;
  }
  
  return dp[0];
}

/**
 * 另一种实现：正向递推（从 0 开始向右计算）
 * 
 * dp[i] = sum(dp[i-j]) / maxPts, j in [1, maxPts] and i-j >= 0 and i-j < k
 * 
 * 使用前缀和优化：
 * - prefix[i] = dp[0] + dp[1] + ... + dp[i-1]
 * - dp[i] = (prefix[i] - prefix[max(0, i-maxPts)]) / maxPts
 */
static double solution2(int n, int k, int maxPts) {
  if (k == 0) return 1.0;
  if (n >= k - 1 + maxPts) return 1.0;
  
  vector<double> dp(n + 1, 0.0);
  vector<double> prefix(n + 2, 0.0);  // prefix[i] = sum(dp[0..i-1])
  
  dp[0] = 1.0;
  prefix[1] = 1.0;
  
  for (int i = 1; i <= n; ++i) {
    // dp[i] = sum of dp[i-j] for j in [1, maxPts] where i-j >= 0 and i-j < k
    // = sum of dp[max(0, i-maxPts) .. min(i-1, k-1)]
    int left = max(0, i - maxPts);
    int right = min(i - 1, k - 1);
    
    if (left <= right) {
      // sum(dp[left..right]) = prefix[right+1] - prefix[left]
      dp[i] = (prefix[right + 1] - prefix[left]) / maxPts;
    }
    
    prefix[i + 1] = prefix[i] + dp[i];
  }
  
  // 最终分数 <= n 的概率 = sum(dp[k..n]) + (如果 k==0 还要加 dp[0])
  // 实际上 dp[i] 表示到达分数 i 的概率，最终分数 <= n 就是 sum(dp[k..n])
  // 但注意：如果 k == 0，说明从开始就停止，分数为 0
  double result = 0.0;
  for (int i = k; i <= n; ++i) {
    result += dp[i];
  }
  
  return result;
}

New21GameSolution::New21GameSolution() {
  setMetaInfo({.id = 837,
               .title = "New 21 Game",
               .url = "https://leetcode.com/problems/new-21-game/"});
  registerStrategy("DP Sliding Window", solution1);
  registerStrategy("DP Prefix Sum", solution2);
}

double New21GameSolution::new21Game(int n, int k, int maxPts) {
  return getSolution()(n, k, maxPts);
}

}  // namespace problem_837
}  // namespace leetcode
