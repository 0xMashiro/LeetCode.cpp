#include "leetcode/problems/inverse-coin-change.h"

namespace leetcode {
namespace problem_3592 {

// 逆向硬币兑换：根据方案数反推硬币面额
// 核心思想：动态规划的逆过程
// 对于金额 i，如果 numWays[i] > dp[i]（仅使用已确定面额的方案数），
// 则差额来自新面额 i 的贡献，说明 i 是一个硬币面额
// 时间复杂度: O(n^2), 空间复杂度: O(n)，其中 n = numWays.size()
static vector<int> solution(vector<int>& numWays) {
  int n = numWays.size();
  
  // numWays 是 1-indexed，但我们用 0-indexed 数组存储
  // numWays[0] 对应金额 0 的方案数
  
  // dp[i] 表示仅用已确定的面额组成金额 i 的方案数
  vector<long long> dp(n + 1, 0);
  dp[0] = 1;  // 组成金额 0 的方案数为 1（什么都不选）
  
  vector<int> coins;  // 找到的硬币面额
  
  for (int i = 1; i <= n; ++i) {
    // numWays[i-1] 对应金额 i 的方案数
    long long targetWays = numWays[i - 1];
    
    if (targetWays < dp[i]) {
      // 不可能：已确定面额就能组成更多方案
      return {};
    }
    
    if (targetWays > dp[i]) {
      // 差额说明 i 是一个硬币面额
      // 差额应该等于 dp[i]（使用面额 i 一次的方案数）
      // 实际上差额可能大于 dp[i]，说明有问题
      long long diff = targetWays - dp[i];
      
      // 检查差额是否合理：新面额 i 的贡献应该是 diff * dp[...]
      // 但更准确地说，我们需要验证 dp[i] + diff == targetWays
      // 并且 diff 应该等于使用新面额的某些组合数
      
      // 实际上，根据硬币兑换的递推关系
      // 如果 i 是新面额，那么对于金额 i，dp_new[i] = dp_old[i] + dp_new[0] = dp[i] + 1
      // 所以 diff 应该至少能让我们更新 dp 数组
      
      coins.push_back(i);
      
      // 更新 dp 数组：加入新面额 i
      // 对于每个金额 j >= i，dp[j] 增加 dp[j - i]
      for (int j = i; j <= n; ++j) {
        dp[j] += dp[j - i];
        // 防止溢出，但题目限制最大 2*10^8，累加可能超过 int
        if (dp[j] > 2e9) {
          // 溢出检查，超过题目限制则认为无效
          return {};
        }
      }
    }
    
    // 更新后再次检查
    if (dp[i] != targetWays) {
      return {};
    }
  }
  
  return coins;
}

InverseCoinChangeSolution::InverseCoinChangeSolution() {
  setMetaInfo({.id = 3592,
               .title = "Inverse Coin Change",
               .url = "https://leetcode.com/problems/inverse-coin-change/"});
  registerStrategy("DP Inverse", solution);
}

vector<int> InverseCoinChangeSolution::findCoins(vector<int>& numWays) {
  return getSolution()(numWays);
}

}  // namespace problem_3592
}  // namespace leetcode
