#include "leetcode/problems/maximum-amount-of-money-robot-can-earn.h"

namespace leetcode {
namespace problem_3418 {

/**
 * 三维动态规划
 * dp[i][j][k] = 到达位置 (i,j) 且使用了 k 次特殊能力时的最大收益
 * 
 * 对于每个格子，机器人可以从上方 (i-1,j) 或左方 (i,j-1) 过来
 * 状态转移：
 * - 不使用特殊能力：dp[i][j][k] = max(dp[i][j][k], dp[prev][k] + coins[i][j])
 * - 使用特殊能力（如果 coins[i][j] < 0 且 k > 0）：
 *   dp[i][j][k] = max(dp[i][j][k], dp[prev][k-1] + 0)
 * 
 * 时间复杂度: O(m * n * 3) = O(mn)
 * 空间复杂度: O(n * 3) = O(n) （滚动数组优化）
 */
static int solution1(vector<vector<int>>& coins) {
  const int m = coins.size();
  if (m == 0) return 0;
  const int n = coins[0].size();
  
  // dp[j][k]: 当前行第 j 列，使用 k 次特殊能力时的最大收益
  // 初始化为负无穷
  const int INF = -1e9;
  vector<vector<int>> dp(n, vector<int>(3, INF));
  
  // 初始化起点 (0, 0)
  // 不使用特殊能力
  dp[0][0] = coins[0][0];
  // 使用特殊能力（如果起点是负数）
  if (coins[0][0] < 0) {
    dp[0][1] = 0;  // 使用一次能力，收益为0
  }
  
  // 初始化第一行
  for (int j = 1; j < n; ++j) {
    for (int k = 0; k < 3; ++k) {
      // 从左边过来，不使用特殊能力
      if (dp[j-1][k] != INF) {
        dp[j][k] = max(dp[j][k], dp[j-1][k] + coins[0][j]);
      }
      // 从左边过来，使用特殊能力
      if (coins[0][j] < 0 && k > 0 && dp[j-1][k-1] != INF) {
        dp[j][k] = max(dp[j][k], dp[j-1][k-1]);  // 使用能力，收益+0
      }
    }
  }
  
  // 处理其余行
  for (int i = 1; i < m; ++i) {
    vector<vector<int>> new_dp(n, vector<int>(3, INF));
    
    // 处理第 i 行的第一列
    for (int k = 0; k < 3; ++k) {
      // 从上方过来，不使用特殊能力
      if (dp[0][k] != INF) {
        new_dp[0][k] = max(new_dp[0][k], dp[0][k] + coins[i][0]);
      }
      // 从上方过来，使用特殊能力
      if (coins[i][0] < 0 && k > 0 && dp[0][k-1] != INF) {
        new_dp[0][k] = max(new_dp[0][k], dp[0][k-1]);  // 使用能力，收益+0
      }
    }
    
    // 处理第 i 行的其他列
    for (int j = 1; j < n; ++j) {
      for (int k = 0; k < 3; ++k) {
        // 从上方 (i-1, j) 过来
        // 不使用特殊能力
        if (dp[j][k] != INF) {
          new_dp[j][k] = max(new_dp[j][k], dp[j][k] + coins[i][j]);
        }
        // 使用特殊能力
        if (coins[i][j] < 0 && k > 0 && dp[j][k-1] != INF) {
          new_dp[j][k] = max(new_dp[j][k], dp[j][k-1]);
        }
        
        // 从左方 (i, j-1) 过来
        // 不使用特殊能力
        if (new_dp[j-1][k] != INF) {
          new_dp[j][k] = max(new_dp[j][k], new_dp[j-1][k] + coins[i][j]);
        }
        // 使用特殊能力
        if (coins[i][j] < 0 && k > 0 && new_dp[j-1][k-1] != INF) {
          new_dp[j][k] = max(new_dp[j][k], new_dp[j-1][k-1]);
        }
      }
    }
    
    dp = move(new_dp);
  }
  
  // 返回右下角三种状态的最大值
  return max({dp[n-1][0], dp[n-1][1], dp[n-1][2]});
}

MaximumAmountOfMoneyRobotCanEarnSolution::MaximumAmountOfMoneyRobotCanEarnSolution() {
  setMetaInfo({
    .id = 3418,
    .title = "Maximum Amount of Money Robot Can Earn",
    .url = "https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/"
  });
  registerStrategy("DP with Rolling Array", solution1);
}

int MaximumAmountOfMoneyRobotCanEarnSolution::maximumAmount(vector<vector<int>>& coins) {
  return getSolution()(coins);
}

}  // namespace problem_3418
}  // namespace leetcode
