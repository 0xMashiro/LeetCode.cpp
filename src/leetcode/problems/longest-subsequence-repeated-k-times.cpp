#include "leetcode/problems/longest-subsequence-repeated-k-times.h"

namespace leetcode {
namespace problem_2014 {

// 检查 candidate 重复 k 次是否是 s 的子序列
static bool isSubsequenceKTimes(const std::string& s, const std::string& candidate, int k) {
  int n = s.length();
  int m = candidate.length();
  int pos = 0;  // 在 s 中的位置
  
  // 需要匹配 candidate 共 k 次
  for (int rep = 0; rep < k; ++rep) {
    for (int i = 0; i < m; ++i) {
      // 在 s 中找到 candidate[i]
      while (pos < n && s[pos] != candidate[i]) {
        ++pos;
      }
      if (pos >= n) {
        return false;  // 没找到
      }
      ++pos;  // 找到了，移动到下一个位置
    }
  }
  return true;
}

// DFS 寻找最长子序列
// 按字典序降序尝试，找到的第一个最长序列就是字典序最大的
static void dfs(const std::string& s, int k, const std::vector<char>& chars,
                std::string& current, std::string& best) {
  // 如果当前序列不可能比最优解更长，剪枝
  // 剩余可用字符数 + 当前长度 < 最优长度，无法超越
  int maxPossible = current.length() + chars.size();
  if (maxPossible < best.length()) {
    return;
  }
  
  // 尝试扩展当前序列
  for (char c : chars) {
    current.push_back(c);
    if (isSubsequenceKTimes(s, current, k)) {
      // 是有效子序列，更新最优解
      if (current.length() > best.length() || 
          (current.length() == best.length() && current > best)) {
        best = current;
      }
      // 继续 DFS 扩展
      dfs(s, k, chars, current, best);
    }
    current.pop_back();
  }
}

static std::string solution1(const std::string& s, int k) {
  int n = s.length();
  
  // 统计每个字符出现次数
  std::vector<int> count(26, 0);
  for (char c : s) {
    count[c - 'a']++;
  }
  
  // 筛选出现次数 >= k 的字符，按字典序降序排列
  std::vector<char> chars;
  for (int i = 25; i >= 0; --i) {  // 'z' 到 'a'
    if (count[i] >= k) {
      chars.push_back('a' + i);
    }
  }
  
  std::string current;
  std::string best;
  dfs(s, k, chars, current, best);
  
  return best;
}

LongestSubsequenceRepeatedKTimesSolution::LongestSubsequenceRepeatedKTimesSolution() {
  setMetaInfo({.id = 2014,
               .title = "Longest Subsequence Repeated k Times",
               .url = "https://leetcode.com/problems/longest-subsequence-repeated-k-times/"});
  registerStrategy("DFS with Pruning", solution1);
}

std::string LongestSubsequenceRepeatedKTimesSolution::longestSubsequenceRepeatedK(
    const std::string& s, int k) {
  return getSolution()(s, k);
}

}  // namespace problem_2014
}  // namespace leetcode
