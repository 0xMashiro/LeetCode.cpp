#include "leetcode/problems/rotated-digits.h"

namespace leetcode {
namespace problem_788 {

// 暴力枚举：遍历 1 到 n，逐个检查每个数字的每一位
// 时间复杂度: O(n log n)，空间复杂度: O(1)
// n ≤ 10^4，完全可行
static int solution1(int n) {
  auto isGood = [](int x) -> bool {
    bool hasChanged = false;
    while (x > 0) {
      int d = x % 10;
      if (d == 3 || d == 4 || d == 7) return false;
      if (d == 2 || d == 5 || d == 6 || d == 9) hasChanged = true;
      x /= 10;
    }
    return hasChanged;
  };

  int count = 0;
  for (int i = 1; i <= n; ++i) {
    if (isGood(i)) ++count;
  }
  return count;
}

// 数位 DP：用记忆化搜索统计 [1, n] 中所有位有效且至少有一位变化的好数
// 时间复杂度: O(log n * 2 * 2 * 10) = O(log n)，空间复杂度: O(log n)
// 状态定义：dp(pos, tight, hasChanged) 表示当前处理到第 pos 位，
// tight 表示是否受上界限制，hasChanged 表示是否已包含变化数字(2/5/6/9)
static int solution2(int n) {
  string s = to_string(n);
  int len = s.size();
  // memo[pos][tight][hasChanged]
  vector<vector<vector<int>>> memo(len,
      vector<vector<int>>(2, vector<int>(2, -1)));

  function<int(int, int, int)> dp = [&](int pos, int tight, int hasChanged) -> int {
    if (pos == len) return hasChanged;
    if (memo[pos][tight][hasChanged] != -1) return memo[pos][tight][hasChanged];

    int limit = tight ? (s[pos] - '0') : 9;
    int res = 0;
    for (int d = 0; d <= limit; ++d) {
      if (d == 3 || d == 4 || d == 7) continue;  // 无效数字，跳过
      int nextTight = tight && (d == limit) ? 1 : 0;
      int nextChanged = hasChanged || (d == 2 || d == 5 || d == 6 || d == 9);
      res += dp(pos + 1, nextTight, nextChanged);
    }

    return memo[pos][tight][hasChanged] = res;
  };

  // dp(0, 1, 0) 统计 [0, n] 中 hasChanged=true 的数字个数（好数）
  // 数字 0 的 hasChanged=false，不会计入结果，因此直接返回即可
  return dp(0, 1, 0);
}

RotatedDigitsSolution::RotatedDigitsSolution() {
  setMetaInfo({.id = 788,
               .title = "Rotated Digits",
               .url = "https://leetcode.com/problems/rotated-digits"});
  registerStrategy({.name = "Brute Force"}, solution1);
  registerStrategy({.name = "Digit DP"}, solution2);
}

int RotatedDigitsSolution::rotatedDigits(int n) {
  return getSolution()(n);
}

}  // namespace problem_788
}  // namespace leetcode
