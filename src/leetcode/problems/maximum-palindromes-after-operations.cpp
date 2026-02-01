#include "leetcode/problems/maximum-palindromes-after-operations.h"

namespace leetcode {
namespace problem_3035 {

// 贪心策略：统计所有可用字符对，优先构造需要较少对数的字符串
// 时间复杂度: O(N + W log W)，N 为总字符数，W 为字符串数量
// 空间复杂度: O(W)
static int solution1(vector<string>& words) {
  // 统计所有字符频次
  vector<int> freq(26, 0);
  for (const auto& word : words) {
    for (char c : word) {
      freq[c - 'a']++;
    }
  }
  
  // 计算总对数
  int totalPairs = 0;
  for (int count : freq) {
    totalPairs += count / 2;
  }
  
  // 计算每个字符串需要的对数
  vector<int> needs;
  needs.reserve(words.size());
  for (const auto& word : words) {
    needs.push_back(word.length() / 2);
  }
  
  // 按需要的最少对数排序（贪心：优先构造短字符串）
  sort(needs.begin(), needs.end());
  
  // 尽可能多地构造回文串
  int ans = 0;
  for (int need : needs) {
    if (totalPairs >= need) {
      totalPairs -= need;
      ans++;
    } else {
      break;
    }
  }
  
  return ans;
}

MaximumPalindromesAfterOperationsSolution::MaximumPalindromesAfterOperationsSolution() {
  setMetaInfo({.id = 3035,
               .title = "Maximum Palindromes After Operations",
               .url = "https://leetcode.com/problems/maximum-palindromes-after-operations/"});
  registerStrategy("Greedy", solution1);
}

int MaximumPalindromesAfterOperationsSolution::maxPalindromesAfterOperations(vector<string>& words) {
  return getSolution()(words);
}

}  // namespace problem_3035
}  // namespace leetcode
