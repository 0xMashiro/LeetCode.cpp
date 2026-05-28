#include "leetcode/problems/longest-common-suffix-queries.h"

namespace leetcode {
namespace problem_3093 {

// 本题唯一合理解为 Trie（反转字符串将后缀匹配转为前缀匹配）
// 暴力 O(N*M*L) 绝对不可行（N,M<=1e4, L<=5e3）
// 核心思想：反转所有字符串，后缀 -> 前缀，用 Trie 匹配最长公共前缀
// 时间复杂度: O(total_len_container + total_len_query)
// 空间复杂度: O(total_len_container * 26)
static vector<int> solution1(vector<string>& wordsContainer, vector<string>& wordsQuery) {
  int n = wordsContainer.size();

  // 全局最优：所有 container 中长度最短的，长度相同取索引最小
  int globalBestIdx = 0;
  for (int i = 1; i < n; ++i) {
    if (wordsContainer[i].length() < wordsContainer[globalBestIdx].length() ||
        (wordsContainer[i].length() == wordsContainer[globalBestIdx].length() && i < globalBestIdx)) {
      globalBestIdx = i;
    }
  }

  // --- Trie 构建 ---
  // 用 vector 池管理节点，children 存子节点索引，-1 表示不存在
  struct TrieNode {
    int bestIdx;         // 经过该节点的最优 container 索引
    int children[26];    // 子节点索引，-1 表示空
    TrieNode() : bestIdx(-1) {
      memset(children, -1, sizeof(children));
    }
  };

  vector<TrieNode> nodes(1);  // nodes[0] = root
  nodes[0].bestIdx = globalBestIdx;

  for (int i = 0; i < n; ++i) {
    const string& word = wordsContainer[i];
    int len = word.length();
    int cur = 0;  // 从根开始

    // 反转遍历字符串，插入 Trie
    for (int j = len - 1; j >= 0; --j) {
      int c = word[j] - 'a';
      if (nodes[cur].children[c] == -1) {
        nodes[cur].children[c] = nodes.size();
        nodes.emplace_back();
      }
      cur = nodes[cur].children[c];

      // 更新当前节点的 bestIdx
      if (nodes[cur].bestIdx == -1) {
        nodes[cur].bestIdx = i;
      } else {
        int curBestLen = wordsContainer[nodes[cur].bestIdx].length();
        if (len < curBestLen || (len == curBestLen && i < nodes[cur].bestIdx)) {
          nodes[cur].bestIdx = i;
        }
      }
    }
  }

  // --- 查询 ---
  int m = wordsQuery.size();
  vector<int> ans(m);

  for (int i = 0; i < m; ++i) {
    const string& query = wordsQuery[i];
    int cur = 0;  // root
    ans[i] = nodes[0].bestIdx;  // 空后缀保底

    // 反转遍历 query，在 Trie 中匹配
    for (int j = query.length() - 1; j >= 0; --j) {
      int c = query[j] - 'a';
      if (nodes[cur].children[c] == -1) break;
      cur = nodes[cur].children[c];
      ans[i] = nodes[cur].bestIdx;
    }
  }

  return ans;
}

LongestCommonSuffixQueriesSolution::LongestCommonSuffixQueriesSolution() {
  setMetaInfo({.id = 3093,
               .title = "Longest Common Suffix Queries",
               .url = "https://leetcode.com/problems/longest-common-suffix-queries/"});
  // 单解：Trie（反转）。暴力法 O(N^2) 在 N=1e4 下不可行，无其他合理范式。
  registerStrategy("Trie Suffix Matching", solution1);
}

vector<int> LongestCommonSuffixQueriesSolution::stringIndices(
    vector<string>& wordsContainer, vector<string>& wordsQuery) {
  return getSolution()(wordsContainer, wordsQuery);
}

}  // namespace problem_3093
}  // namespace leetcode
