#include "leetcode/problems/paths-in-matrix-whose-sum-is-divisible-by-k.h"

namespace leetcode {
namespace problem_2435 {

static constexpr int MOD = 1000000007;

// 动态规划 + 滚动数组优化
// dp[j][r] 表示当前行第 j 列，路径和模 k 等于 r 的路径数
// 时间复杂度: O(m * n * k), 空间复杂度: O(n * k)
static int solution1(vector<vector<int>>& grid, int k) {
  const int m = grid.size();
  const int n = grid[0].size();
  
  // dp[j][r]: 当前行第 j 列，路径和模 k 等于 r 的路径数
  vector<vector<long long>> dp(n, vector<long long>(k, 0));
  
  // 初始化起点
  dp[0][grid[0][0] % k] = 1;
  
  // 初始化第一行（只能从左边过来）
  for (int j = 1; j < n; ++j) {
    for (int r = 0; r < k; ++r) {
      int new_r = (r + grid[0][j]) % k;
      dp[j][new_r] = (dp[j][new_r] + dp[j-1][r]) % MOD;
    }
  }
  
  // 处理其余行
  for (int i = 1; i < m; ++i) {
    // 新的 dp 数组
    vector<vector<long long>> new_dp(n, vector<long long>(k, 0));
    
    // 第一列：只能从上方过来
    for (int r = 0; r < k; ++r) {
      int new_r = (r + grid[i][0]) % k;
      new_dp[0][new_r] = (new_dp[0][new_r] + dp[0][r]) % MOD;
    }
    
    // 其余列：可以从上方或左方过来
    for (int j = 1; j < n; ++j) {
      for (int r = 0; r < k; ++r) {
        int new_r = (r + grid[i][j]) % k;
        // 从上方过来 (dp[j][r])
        new_dp[j][new_r] = (new_dp[j][new_r] + dp[j][r]) % MOD;
        // 从左方过来 (new_dp[j-1][r])
        new_dp[j][new_r] = (new_dp[j][new_r] + new_dp[j-1][r]) % MOD;
      }
    }
    
    dp = std::move(new_dp);
  }
  
  return static_cast<int>(dp[n-1][0]);
}

PathsInMatrixWhoseSumIsDivisibleByKSolution::PathsInMatrixWhoseSumIsDivisibleByKSolution() {
  setMetaInfo({.id = 2435,
               .title = "Paths in Matrix Whose Sum Is Divisible by K",
               .url = "https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/"});
  registerStrategy("DP with Rolling Array", solution1);
}

int PathsInMatrixWhoseSumIsDivisibleByKSolution::numberOfPaths(vector<vector<int>>& grid, int k) {
  return getSolution()(grid, k);
}

}  // namespace problem_2435
}  // namespace leetcode