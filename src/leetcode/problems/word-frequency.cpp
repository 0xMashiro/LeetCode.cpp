#include "leetcode/problems/word-frequency.h"

#include <sstream>

namespace leetcode {
namespace problem_192 {

// 哈希表统计 + 排序
// 时间复杂度: O(n log n)，其中 n 是不同单词的数量
// 空间复杂度: O(n)，哈希表存储所有单词
static vector<pair<string, int>> solution1(const string& content) {
  unordered_map<string, int> freq;
  stringstream ss(content);
  string word;
  
  // 读取每个单词并统计频率
  while (ss >> word) {
    freq[word]++;
  }
  
  // 转换为 vector 以便排序
  vector<pair<string, int>> result(freq.begin(), freq.end());
  
  // 按频率降序排序（题目保证频率唯一，不需要处理相等的情况）
  sort(result.begin(), result.end(), 
       [](const pair<string, int>& a, const pair<string, int>& b) {
         return a.second > b.second;
       });
  
  return result;
}

WordFrequencySolution::WordFrequencySolution() {
  setMetaInfo({.id = 192,
               .title = "Word Frequency",
               .url = "https://leetcode.com/problems/word-frequency/"});
  registerStrategy("Hash Table + Sort", solution1);
}

vector<pair<string, int>> WordFrequencySolution::wordFrequency(const string& content) {
  return getSolution()(content);
}

}  // namespace problem_192
}  // namespace leetcode
