#include "leetcode/problems/profitable-schemes.h"

namespace leetcode {
namespace problem_879 {

static int solution1(int n, int minProfit, vector<int>& group, vector<int>& profit) {
  const int MOD = 1000000007;
  int m = group.size();
  // dp[i][j] = 使用 i 名员工，获得至少 j 利润的方案数
  vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
  dp[0][0] = 1;  // 什么都不做：0 员工，0 利润
  
  for (int k = 0; k < m; ++k) {
    int g = group[k];
    int p = profit[k];
    // 逆序更新，避免同一工作多次使用
    for (int i = n; i >= g; --i) {
      for (int j = minProfit; j >= 0; --j) {
        // 选择当前工作：利润取 min(minProfit, j + p)，因为超过 minProfit 的算作 minProfit
        int newProfit = min(minProfit, j + p);
        dp[i][newProfit] = (dp[i][newProfit] + dp[i - g][j]) % MOD;
      }
    }
  }
  
  // 统计所有使用 <= n 名员工，且利润 >= minProfit 的方案
  int ans = 0;
  for (int i = 0; i <= n; ++i) {
    ans = (ans + dp[i][minProfit]) % MOD;
  }
  return ans;
}

ProfitableSchemesSolution::ProfitableSchemesSolution() {
  setMetaInfo({
      .id = 879,
      .title = "Profitable Schemes",
      .url = "https://leetcode.com/problems/profitable-schemes"
  });
  registerStrategy("Brute Force", solution1);
}

int ProfitableSchemesSolution::profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
  return getSolution()(n, minProfit, group, profit);
}

}  // namespace problem_879
}  // namespace leetcode
