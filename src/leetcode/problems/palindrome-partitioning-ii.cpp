
#include "leetcode/problems/palindrome-partitioning-ii.h"

namespace leetcode {
namespace problem_132 {

// 动态规划解法
// 1. 先用 isPal[i][j] 预处理所有子串是否是回文
// 2. 再用 dp[i] 表示 s[0..i] 的最少切割次数
// 时间复杂度: O(n²), 空间复杂度: O(n²)
static int solution1(string s) {
  const int n = s.size();
  if (n <= 1) return 0;

  // isPal[i][j] = true 表示 s[i..j] 是回文
  vector<vector<bool>> isPal(n, vector<bool>(n, false));

  // 单个字符都是回文
  for (int i = 0; i < n; ++i) {
    isPal[i][i] = true;
  }

  // 处理长度 >= 2 的子串
  for (int len = 2; len <= n; ++len) {
    for (int i = 0; i <= n - len; ++i) {
      int j = i + len - 1;
      if (len == 2) {
        isPal[i][j] = (s[i] == s[j]);
      } else {
        isPal[i][j] = (s[i] == s[j]) && isPal[i + 1][j - 1];
      }
    }
  }

  // dp[i] 表示 s[0..i] 的最少切割次数
  vector<int> dp(n, n);  // 初始化为最大值（最坏情况每个字符切一刀）

  for (int i = 0; i < n; ++i) {
    if (isPal[0][i]) {
      // s[0..i] 本身就是回文，不需要切割
      dp[i] = 0;
    } else {
      // 枚举分割点 j
      for (int j = 1; j <= i; ++j) {
        if (isPal[j][i]) {
          // s[j..i] 是回文，可以在这里分割
          dp[i] = min(dp[i], dp[j - 1] + 1);
        }
      }
    }
  }

  return dp[n - 1];
}

// 优化空间复杂度的解法：使用中心扩展预处理回文
// 时间复杂度: O(n²), 空间复杂度: O(n)
static int solution2(string s) {
  const int n = s.size();
  if (n <= 1) return 0;

  vector<int> dp(n, n);  // dp[i] 表示 s[0..i] 的最少切割次数

  // 辅助函数：更新以中心扩展的回文子串对应的 dp 值
  auto updatePalindrome = [&](int left, int right) {
    while (left >= 0 && right < n && s[left] == s[right]) {
      if (left == 0) {
        // s[0..right] 是回文
        dp[right] = 0;
      } else {
        // s[left..right] 是回文，可以从 left-1 处切割
        dp[right] = min(dp[right], dp[left - 1] + 1);
      }
      --left;
      ++right;
    }
  };

  // 枚举所有中心点
  for (int i = 0; i < n; ++i) {
    // 奇数长度回文（中心是一个字符）
    updatePalindrome(i, i);
    // 偶数长度回文（中心是两个字符之间）
    if (i + 1 < n) {
      updatePalindrome(i, i + 1);
    }
  }

  return dp[n - 1];
}

PalindromePartitioningIiSolution::PalindromePartitioningIiSolution() {
  setMetaInfo({.id = 132,
               .title = "Palindrome Partitioning II",
               .url = "https://leetcode.com/problems/palindrome-partitioning-ii/"});
  registerStrategy("DP with Preprocessing", solution1);
  registerStrategy("Center Expansion Optimized", solution2);
}

int PalindromePartitioningIiSolution::minCut(string s) {
  return getSolution()(s);
}

}  // namespace problem_132
}  // namespace leetcode
