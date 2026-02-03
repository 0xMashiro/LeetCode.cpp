#include "leetcode/problems/counting-bits.h"

namespace leetcode {
namespace problem_338 {

// 动态规划解法：利用之前计算的结果
// ans[i] = ans[i >> 1] + (i & 1)
// i 中 1 的个数 = i/2 中 1 的个数 + i 的最低位
// 时间复杂度: O(n), 空间复杂度: O(n) 用于返回结果
static vector<int> solution1(int n) {
  vector<int> ans(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    ans[i] = ans[i >> 1] + (i & 1);
  }
  return ans;
}

// 另一种 DP 思路：利用最低位的 1
// i & (i - 1) 会清除 i 的最低位的 1
// ans[i] = ans[i & (i - 1)] + 1
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution2(int n) {
  vector<int> ans(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    ans[i] = ans[i & (i - 1)] + 1;
  }
  return ans;
}

// 使用内置函数（最简洁，但在面试中可能不被接受）
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<int> solution3(int n) {
  vector<int> ans;
  ans.reserve(n + 1);
  for (int i = 0; i <= n; ++i) {
    ans.push_back(__builtin_popcount(i));
  }
  return ans;
}

CountingBitsSolution::CountingBitsSolution() {
  setMetaInfo({.id = 338,
               .title = "Counting Bits",
               .url = "https://leetcode.com/problems/counting-bits/"});
  registerStrategy("DP with i>>1", solution1);
  registerStrategy("DP with i&(i-1)", solution2);
  registerStrategy("Builtin popcount", solution3);
}

vector<int> CountingBitsSolution::countBits(int n) {
  return getSolution()(n);
}

}  // namespace problem_338
}  // namespace leetcode
