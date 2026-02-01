#include "leetcode/problems/word-subsets.h"

namespace leetcode {
namespace problem_916 {

// 计算字符串的字符频率数组
static array<int, 26> getFreq(const string& s) {
  array<int, 26> freq{};
  freq.fill(0);
  for (char c : s) {
    freq[c - 'a']++;
  }
  return freq;
}

// 合并 words2 中所有单词的字符频率需求
// 对于每个字符，取所有单词中的最大出现次数
static array<int, 26> mergeRequirements(vector<string>& words2) {
  array<int, 26> req{};
  req.fill(0);
  for (const string& word : words2) {
    array<int, 26> freq = getFreq(word);
    for (int i = 0; i < 26; i++) {
      req[i] = max(req[i], freq[i]);
    }
  }
  return req;
}

// 检查单词 word 是否满足字符频率需求 req
static bool isUniversal(const string& word, const array<int, 26>& req) {
  array<int, 26> freq = getFreq(word);
  for (int i = 0; i < 26; i++) {
    if (freq[i] < req[i]) {
      return false;
    }
  }
  return true;
}

// 主解法：合并需求 + 逐一检查
// 时间复杂度: O(N * L + M * L)，其中 N=words1.length, M=words2.length, L=单词平均长度
// 空间复杂度: O(1)，只使用固定大小的频率数组
static vector<string> solution(vector<string>& words1, vector<string>& words2) {
  // 合并 words2 的所有需求
  array<int, 26> req = mergeRequirements(words2);
  
  vector<string> result;
  // 检查 words1 中每个单词
  for (string& word : words1) {
    if (isUniversal(word, req)) {
      result.push_back(word);
    }
  }
  return result;
}

WordSubsetsSolution::WordSubsetsSolution() {
  setMetaInfo({.id = 916,
               .title = "Word Subsets",
               .url = "https://leetcode.com/problems/word-subsets/"});
  registerStrategy("Merge Requirements", solution);
}

vector<string> WordSubsetsSolution::wordSubsets(vector<string>& words1, vector<string>& words2) {
  return getSolution()(words1, words2);
}

}  // namespace problem_916
}  // namespace leetcode
