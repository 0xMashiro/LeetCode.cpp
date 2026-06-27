#include "leetcode/problems/find-the-maximum-number-of-elements-in-subset.h"

#include <algorithm>
#include <cmath>
#include <unordered_map>

namespace leetcode {
namespace problem_3020 {

// 哈希表 + 枚举顶点向下开方
// 时间复杂度: O(n + d * log log M)，d 为不同元素数，M = 1e9
// 空间复杂度: O(d)
static int solution1(std::vector<int>& nums) {
  std::unordered_map<int, int> freq;
  for (int x : nums) {
    freq[x]++;
  }

  int ans = 0;

  // 特殊处理 1：1 的所有幂都是 1，序列长度必须是奇数
  if (freq.count(1)) {
    int c = freq[1];
    // 最大奇数 <= c
    ans = std::max(ans, (c % 2 == 1) ? c : (c - 1));
  }

  // 枚举每个不同值作为候选顶点
  for (const auto& [v, f] : freq) {
    if (v == 1) continue;  // 1 已处理

    int cur = 1;  // 顶点贡献 1 个
    long long val = v;

    while (true) {
      // 尝试向下开方
      long long r = static_cast<long long>(std::sqrt(static_cast<long double>(val)));
      // 处理浮点误差：尝试 r, r+1, r-1
      if (r * r > val) {
        r--;
      } else if ((r + 1) * (r + 1) <= val) {
        r++;
      }
      if (r * r != val) break;  // 不是完全平方数
      if (r > 1000000000) break;  // 超出 nums 元素范围

      int prev = static_cast<int>(r);
      auto it = freq.find(prev);
      if (it == freq.end() || it->second < 2) break;  // 不足以作为非顶点

      cur += 2;
      val = prev;
    }

    ans = std::max(ans, cur);
  }

  return ans;
}

FindTheMaximumNumberOfElementsInSubsetSolution::FindTheMaximumNumberOfElementsInSubsetSolution() {
  setMetaInfo({.id = 3020,
               .title = "Find the Maximum Number of Elements in Subset",
               .url = "https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/"});
  registerStrategy(
      {.name = "Hash Table + Enumeration",
       .expected = "Accepted",
       .time_complexity = "O(n + d * log log M)",
       .space_complexity = "O(d)",
       .tags = {"Array", "Hash Table", "Enumeration"}},
      solution1);
}

int FindTheMaximumNumberOfElementsInSubsetSolution::maximumLength(std::vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3020
}  // namespace leetcode
