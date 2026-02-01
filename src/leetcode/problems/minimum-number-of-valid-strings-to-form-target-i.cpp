#include "leetcode/problems/minimum-number-of-valid-strings-to-form-target-i.h"

namespace leetcode {
namespace problem_3291 {

// Trie 节点结构
struct TrieNode {
  TrieNode* children[26];
  TrieNode() {
    for (int i = 0; i < 26; ++i) {
      children[i] = nullptr;
    }
  }
  ~TrieNode() {
    for (int i = 0; i < 26; ++i) {
      delete children[i];
    }
  }
};

// 使用 Trie + 动态规划
// 时间复杂度: O(|target| * max_word_length + sum(|words[i]|))
// 空间复杂度: O(sum(|words[i]|) + |target|)
static int solution1(vector<string>& words, string target) {
  const int n = target.size();
  const int INF = 1e9;
  
  // 构建 Trie
  TrieNode* root = new TrieNode();
  for (const string& word : words) {
    TrieNode* node = root;
    for (char c : word) {
      int idx = c - 'a';
      if (!node->children[idx]) {
        node->children[idx] = new TrieNode();
      }
      node = node->children[idx];
    }
  }
  
  // dp[i] 表示拼出 target[0..i-1]（前i个字符）所需的最少有效字符串数
  vector<int> dp(n + 1, INF);
  dp[0] = 0;
  
  // 对于每个起始位置，用 Trie 查找所有可能的匹配
  for (int i = 0; i < n; ++i) {
    if (dp[i] >= INF) continue;  // 无法到达此位置
    
    TrieNode* node = root;
    // 从位置 i 开始，尝试匹配尽可能长的前缀
    for (int j = i; j < n; ++j) {
      int idx = target[j] - 'a';
      if (!node->children[idx]) break;  // 没有匹配的前缀了
      node = node->children[idx];
      // 找到一个有效前缀 target[i..j]，可以更新 dp[j+1]
      dp[j + 1] = min(dp[j + 1], dp[i] + 1);
    }
  }
  
  delete root;
  
  return dp[n] >= INF ? -1 : dp[n];
}

MinimumNumberOfValidStringsToFormTargetISolution::MinimumNumberOfValidStringsToFormTargetISolution() {
  setMetaInfo({.id = 3291,
               .title = "Minimum Number of Valid Strings to Form Target I",
               .url = "https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/"});
  registerStrategy("Trie + DP", solution1);
}

int MinimumNumberOfValidStringsToFormTargetISolution::minValidStrings(vector<string>& words, string target) {
  return getSolution()(words, target);
}

}  // namespace problem_3291
}  // namespace leetcode
