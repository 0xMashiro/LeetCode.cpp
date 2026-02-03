#include "leetcode/problems/decode-ways.h"

namespace leetcode {
namespace problem_91 {

// 动态规划解法
// 状态定义：dp[i] 表示前 i 个字符（s[0..i-1]）的解码方式数
// 状态转移：
//   - 如果 s[i-1] != '0'，可以单独解码，dp[i] += dp[i-1]
//   - 如果 s[i-2:i] 在 "10"-"26" 之间，可以组合解码，dp[i] += dp[i-2]
// 时间复杂度: O(n), 空间复杂度: O(n) -> 可优化至 O(1)
static int solution_dp(string s) {
  const int n = s.size();
  if (n == 0 || s[0] == '0') return 0;

  // dp[i] 表示前 i 个字符的解码方式数
  vector<int> dp(n + 1, 0);
  dp[0] = 1;  // 空串有1种解码方式
  dp[1] = 1;  // 第一个字符不是'0'，有1种解码方式

  for (int i = 2; i <= n; ++i) {
    // 单独解码当前字符（如果当前字符不是 '0'）
    int one_digit = s[i - 1] - '0';
    if (one_digit >= 1 && one_digit <= 9) {
      dp[i] += dp[i - 1];
    }

    // 与前一个字符组合解码（如果组合在 10-26 之间）
    int two_digits = (s[i - 2] - '0') * 10 + one_digit;
    if (two_digits >= 10 && two_digits <= 26) {
      dp[i] += dp[i - 2];
    }

    // 如果当前字符无法单独解码，也无法与前一个组合，则无解
    if (dp[i] == 0) return 0;
  }

  return dp[n];
}

// 空间优化版本
// 只保留前两个状态的值，空间复杂度降至 O(1)
static int solution_dp_optimized(string s) {
  const int n = s.size();
  if (n == 0 || s[0] == '0') return 0;

  int prev2 = 1;  // dp[i-2]
  int prev1 = 1;  // dp[i-1]

  for (int i = 2; i <= n; ++i) {
    int curr = 0;

    // 单独解码当前字符
    int one_digit = s[i - 1] - '0';
    if (one_digit >= 1 && one_digit <= 9) {
      curr += prev1;
    }

    // 与前一个字符组合解码
    int two_digits = (s[i - 2] - '0') * 10 + one_digit;
    if (two_digits >= 10 && two_digits <= 26) {
      curr += prev2;
    }

    if (curr == 0) return 0;  // 无法解码

    prev2 = prev1;
    prev1 = curr;
  }

  return prev1;
}

DecodeWaysSolution::DecodeWaysSolution() {
  setMetaInfo({.id = 91,
               .title = "Decode Ways",
               .url = "https://leetcode.com/problems/decode-ways/"});
  registerStrategy("DP", solution_dp);
  registerStrategy("DP Optimized", solution_dp_optimized);
}

int DecodeWaysSolution::numDecodings(string s) {
  return getSolution()(s);
}

}  // namespace problem_91
}  // namespace leetcode
