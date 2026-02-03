#include "leetcode/problems/unique-paths.h"

namespace leetcode {
namespace problem_62 {

// 动态规划：二维数组
// 时间复杂度: O(m*n), 空间复杂度: O(m*n)
static int solution1(int m, int n) {
  // dp[i][j] 表示到达 (i,j) 的路径数
  vector<vector<int>> dp(m, vector<int>(n, 1));
  
  // 第一行和第一列初始化为 1（只有一条路径）
  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      dp[i][j] = dp[i-1][j] + dp[i][j-1];
    }
  }
  
  return dp[m-1][n-1];
}

// 动态规划：空间优化（滚动数组）
// 时间复杂度: O(m*n), 空间复杂度: O(n)
static int solution2(int m, int n) {
  // 只需要一维数组，dp[j] 表示当前行第 j 列的路径数
  vector<int> dp(n, 1);
  
  for (int i = 1; i < m; ++i) {
    for (int j = 1; j < n; ++j) {
      dp[j] += dp[j-1];
    }
  }
  
  return dp[n-1];
}

// 数学组合数方法
// 总共需要走 (m-1) 次向下和 (n-1) 次向右，总共 m+n-2 步
// 问题转化为从 m+n-2 步中选择 m-1 步向下（或 n-1 步向右）
// 时间复杂度: O(min(m,n)), 空间复杂度: O(1)
static int solution3(int m, int n) {
  // 计算组合数 C(m+n-2, m-1) 或 C(m+n-2, n-1)
  // 选择较小的进行计算，减少计算量
  long long result = 1;
  int k = min(m - 1, n - 1);
  int total = m + n - 2;
  
  for (int i = 1; i <= k; ++i) {
    result = result * (total - i + 1) / i;
  }
  
  return static_cast<int>(result);
}

UniquePathsSolution::UniquePathsSolution() {
  setMetaInfo({.id = 62,
               .title = "Unique Paths",
               .url = "https://leetcode.com/problems/unique-paths/"});
  registerStrategy("DP 2D", solution1);
  registerStrategy("DP 1D", solution2);
  registerStrategy("Math Combination", solution3);
}

int UniquePathsSolution::uniquePaths(int m, int n) {
  return getSolution()(m, n);
}

}  // namespace problem_62
}  // namespace leetcode
