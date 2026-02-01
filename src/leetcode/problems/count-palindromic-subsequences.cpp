
#include "leetcode/problems/count-palindromic-subsequences.h"

namespace leetcode {
namespace problem_2484 {

static const int MOD = 1000000007;

// 核心思路：长度为5的回文形如 ABCBA
// 枚举中间字符C的位置，统计左边AB的数量和右边BA的数量
// 时间复杂度: O(n * 100), 空间复杂度: O(n * 100)
static int solution1(string s) {
  int n = s.size();
  if (n < 5) return 0;
  
  // left[i][a][b] 表示位置i左边（即 s[0..i-1] 中），形如 'ab' 的子序列数量
  // a 和 b 都是 0-9 的数字，我们用 10*10=100 维数组展平，索引为 a*10+b
  vector<array<long long, 100>> left(n);
  // right[i][a][b] 表示位置i右边（即 s[i+1..n-1] 中），形如 'ab' 的子序列数量
  vector<array<long long, 100>> right(n);
  
  // 计算前缀 left
  array<long long, 10> cnt = {};
  for (int i = 0; i < n; i++) {
    int c = s[i] - '0';
    if (i > 0) {
      left[i] = left[i-1];
      for (int x = 0; x < 10; x++) {
        left[i][x * 10 + c] = (left[i][x * 10 + c] + cnt[x]) % MOD;
      }
    }
    cnt[c]++;
  }
  
  // 计算后缀 right
  // 方法：从左往右遍历右边部分，类似于 left 的计算
  // 但为了效率，我们从右往左递推
  // right[i] 表示 s[i+1..n-1] 中的 "ab" 模式数量
  // right[i] 可以从 right[i+1] 和位置 i+1 的字符推导
  
  // 重新思考：从右往左遍历，构建 "ab" 模式
  // 当在位置 i 遇到字符 c，右边已遍历的字符形成一些 "ab" 模式
  // 现在加入 c（c 在更左边），c 可以作为 "ab" 中的 a，与右边所有的 b 组成 "cb"
  cnt = {};
  for (int i = n - 1; i >= 0; i--) {
    int c = s[i] - '0';
    // cnt[x] 表示位置 i+1 到 n-1 中字符 x 的数量
    // right[i] 表示位置 i+1 到 n-1 中的 "ab" 模式数量
    if (i < n - 1) {
      right[i] = right[i+1];
      // 当前字符 c 可以作为 "ab" 中的 a，与右边所有的 b 组成 "cb"
      for (int b = 0; b < 10; b++) {
        right[i][c * 10 + b] = (right[i][c * 10 + b] + cnt[b]) % MOD;
      }
    }
    cnt[c]++;
  }
  
  // 枚举中间位置
  long long ans = 0;
  for (int i = 2; i < n - 2; i++) {
    for (int a = 0; a < 10; a++) {
      for (int b = 0; b < 10; b++) {
        // 左边形如 'ab' 的数量（a 在前，b 在后）
        long long left_cnt = left[i-1][a * 10 + b];
        // 右边形如 'ba' 的数量（b 在前，a 在后）
        // right 中存储的是 "xy" 模式，所以 "ba" 对应 right[i+1][b * 10 + a]
        long long right_cnt = right[i+1][b * 10 + a];
        ans = (ans + left_cnt * right_cnt) % MOD;
      }
    }
  }
  
  return (int)ans;
}

CountPalindromicSubsequencesSolution::CountPalindromicSubsequencesSolution() {
  setMetaInfo({.id = 2484,
               .title = "Count Palindromic Subsequences",
               .url = "https://leetcode.com/problems/count-palindromic-subsequences/"});
  registerStrategy("DP with Prefix/Suffix", solution1);
}

int CountPalindromicSubsequencesSolution::countPalindromes(string s) {
  return getSolution()(s);
}

}  // namespace problem_2484
}  // namespace leetcode
