#include "leetcode/problems/count-different-palindromic-subsequences.h"

namespace leetcode {
namespace problem_730 {

static const int MOD = 1e9 + 7;

// 区间动态规划
// dp[i][j] = s[i:j+1] 中不同回文子序列的数量
// 时间复杂度: O(n²), 空间复杂度: O(n²)
static int solution1(string s) {
  const int n = s.size();
  // dp[i][j] 表示子串 s[i:j+1] 中不同回文子序列的数量
  vector<vector<long long>> dp(n, vector<long long>(n, 0));
  
  // 单个字符是回文
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
  }
  
  // 区间 DP，长度从小到大
  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i + len - 1 < n; ++i) {
      int j = i + len - 1;
      
      if (s[i] != s[j]) {
        // s[i] != s[j]: 没有同时包含 s[i] 和 s[j] 的新回文
        // dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]
        dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
      } else {
        // s[i] == s[j]
        char c = s[i];
        // 在 (i, j) 范围内查找相同的字符
        int left = i + 1, right = j - 1;
        
        // 找到左边第一个等于 c 的位置
        while (left <= right && s[left] != c) ++left;
        // 找到右边第一个等于 c 的位置
        while (left <= right && s[right] != c) --right;
        
        if (left > right) {
          // 中间没有 c，如 "bcb"
          // 新形成的回文: c, cc, 以及中间所有回文的两边加 c
          // dp[i][j] = dp[i+1][j-1] * 2 + 2
          dp[i][j] = dp[i + 1][j - 1] * 2 + 2;
        } else if (left == right) {
          // 中间只有一个 c，如 "bcc"
          // 新形成的回文: c, cc, ccc, 以及中间所有回文的两边加 c
          // 但单个 c 被重复计算了，需要减去 1
          // dp[i][j] = dp[i+1][j-1] * 2 + 1
          dp[i][j] = dp[i + 1][j - 1] * 2 + 1;
        } else {
          // 中间有两个或更多 c，如 "bcbb"
          // 需要减去重复计算的部分：s[left:right+1] 中的回文
          // dp[i][j] = dp[i+1][j-1] * 2 - dp[left+1][right-1]
          dp[i][j] = dp[i + 1][j - 1] * 2 - dp[left + 1][right - 1];
        }
      }
      
      dp[i][j] = (dp[i][j] % MOD + MOD) % MOD;
    }
  }
  
  return (int)dp[0][n - 1];
}

CountDifferentPalindromicSubsequencesSolution::CountDifferentPalindromicSubsequencesSolution() {
  setMetaInfo({.id = 730,
               .title = "Count Different Palindromic Subsequences",
               .url = "https://leetcode.com/problems/count-different-palindromic-subsequences/"});
  registerStrategy("DP with Interval", solution1);
}

int CountDifferentPalindromicSubsequencesSolution::countPalindromicSubsequences(string s) {
  return getSolution()(s);
}

}  // namespace problem_730
}  // namespace leetcode
