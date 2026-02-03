
#include "leetcode/problems/strange-printer.h"

namespace leetcode {
namespace problem_664 {

// 区间 DP 解法
// dp[i][j] 表示打印子串 s[i..j] 所需的最少次数
// 时间复杂度: O(n³), 空间复杂度: O(n²)
static int solution1(string s) {
  const int n = s.size();
  if (n == 0) return 0;
  
  // dp[i][j] 表示打印 s[i..j] 的最少次数
  vector<vector<int>> dp(n, vector<int>(n, 0));
  
  // 单个字符只需要打印 1 次
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
  }
  
  // 按区间长度从小到大计算
  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i + len - 1 < n; ++i) {
      int j = i + len - 1;
      
      // 初始化为最坏情况：s[i] 单独打印，其余部分另外打印
      dp[i][j] = dp[i][i] + dp[i + 1][j];
      
      // 如果 s[i] == s[j]，可以在打印 s[i..j-1] 时顺便打印 s[j]
      if (s[i] == s[j]) {
        dp[i][j] = min(dp[i][j], dp[i][j - 1]);
      }
      
      // 枚举分割点 k，尝试将区间分成两部分
      for (int k = i + 1; k < j; ++k) {
        if (s[i] == s[k]) {
          // 如果 s[i] == s[k]，可以在打印 s[i..k-1] 时覆盖 s[k]
          dp[i][j] = min(dp[i][j], dp[i][k - 1] + dp[k + 1][j]);
        }
      }
    }
  }
  
  return dp[0][n - 1];
}

// 优化版本：预处理去除连续重复字符
static int solution2(string s) {
  // 去除连续重复字符，如 "aaabbb" -> "ab"
  string t;
  for (char c : s) {
    if (t.empty() || t.back() != c) {
      t.push_back(c);
    }
  }
  
  const int n = t.size();
  if (n == 0) return 0;
  
  // dp[i][j] 表示打印 t[i..j] 的最少次数
  vector<vector<int>> dp(n, vector<int>(n, 0));
  
  for (int i = 0; i < n; ++i) {
    dp[i][i] = 1;
  }
  
  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i + len - 1 < n; ++i) {
      int j = i + len - 1;
      
      // 初始：先打印 t[i]，再打印 t[i+1..j]
      dp[i][j] = 1 + dp[i + 1][j];
      
      // 如果在 (i, j] 范围内有和 t[i] 相同的字符，可以尝试合并打印
      for (int k = i + 1; k <= j; ++k) {
        if (t[i] == t[k]) {
          // 打印 t[i..k-1] 时顺便覆盖 t[k]
          int left = (k == i + 1) ? 0 : dp[i + 1][k - 1];
          int right = (k == j) ? 0 : dp[k + 1][j];
          dp[i][j] = min(dp[i][j], dp[i][k - 1] + right);
        }
      }
    }
  }
  
  return dp[0][n - 1];
}

StrangePrinterSolution::StrangePrinterSolution() {
  setMetaInfo({.id = 664,
               .title = "Strange Printer",
               .url = "https://leetcode.com/problems/strange-printer/"});
  registerStrategy("Interval DP", solution1);
  registerStrategy("Optimized DP", solution2);
}

int StrangePrinterSolution::strangePrinter(string s) {
  return getSolution()(s);
}

}  // namespace problem_664
}  // namespace leetcode
