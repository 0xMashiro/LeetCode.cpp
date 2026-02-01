#include "leetcode/problems/interleaving-string.h"

namespace leetcode {
namespace problem_97 {

// 动态规划：dp[i][j] 表示 s1[0..i-1] 和 s2[0..j-1] 是否能交错组成 s3[0..i+j-1]
// 时间复杂度: O(m*n), 空间复杂度: O(m*n)
static bool solution1(string s1, string s2, string s3) {
  const int m = s1.length();
  const int n = s2.length();
  
  // 长度检查
  if (m + n != (int)s3.length()) {
    return false;
  }
  
  // dp[i][j]: s1前i个和s2前j个能否组成s3前i+j个
  vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
  
  // 初始化: 空字符串匹配空字符串
  dp[0][0] = true;
  
  // 第一行: 只用s2匹配s3
  for (int j = 1; j <= n; ++j) {
    dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
  }
  
  // 第一列: 只用s1匹配s3
  for (int i = 1; i <= m; ++i) {
    dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
  }
  
  // 状态转移
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      // 从s1取或从s2取
      dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                 (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
    }
  }
  
  return dp[m][n];
}

// 动态规划 - 空间优化：使用一维数组
// 时间复杂度: O(m*n), 空间复杂度: O(n)
static bool solution2(string s1, string s2, string s3) {
  const int m = s1.length();
  const int n = s2.length();
  
  if (m + n != (int)s3.length()) {
    return false;
  }
  
  // 优化：让s2是较短的字符串，减少空间使用
  if (n > m) {
    return solution2(s2, s1, s3);
  }
  
  // dp[j] 表示当前行第j列的值
  vector<bool> dp(n + 1, false);
  dp[0] = true;
  
  // 初始化第一行
  for (int j = 1; j <= n; ++j) {
    dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);
  }
  
  for (int i = 1; i <= m; ++i) {
    // 更新第0列
    dp[0] = dp[0] && (s1[i - 1] == s3[i - 1]);
    
    for (int j = 1; j <= n; ++j) {
      dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
              (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
    }
  }
  
  return dp[n];
}

InterleavingStringSolution::InterleavingStringSolution() {
  setMetaInfo({.id = 97,
               .title = "Interleaving String",
               .url = "https://leetcode.com/problems/interleaving-string/"});
  registerStrategy("DP 2D", solution1);
  registerStrategy("DP 1D", solution2);
}

bool InterleavingStringSolution::isInterleave(string s1, string s2, string s3) {
  return getSolution()(s1, s2, s3);
}

}  // namespace problem_97
}  // namespace leetcode
