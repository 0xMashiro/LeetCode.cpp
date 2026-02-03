
#include "leetcode/problems/sort-characters-by-frequency.h"

namespace leetcode {
namespace problem_451 {

// 哈希表统计频率 + 按频率排序
// 时间复杂度: O(n + k log k) = O(n), k 为不同字符数
// 空间复杂度: O(k)
static string solution1(string s) {
  // 统计每个字符的频率
  unordered_map<char, int> freq;
  for (char c : s) {
    freq[c]++;
  }
  
  // 将字符按频率降序排序
  vector<pair<char, int>> chars(freq.begin(), freq.end());
  sort(chars.begin(), chars.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;  // 按频率降序
  });
  
  // 构建结果字符串
  string result;
  result.reserve(s.size());  // 预分配空间
  for (const auto& [ch, count] : chars) {
    result.append(count, ch);  // 将字符 ch 重复 count 次追加到结果
  }
  
  return result;
}

// 桶排序优化：按频率分桶
// 时间复杂度: O(n), 空间复杂度: O(n)
static string solution2(string s) {
  // 统计每个字符的频率
  unordered_map<char, int> freq;
  for (char c : s) {
    freq[c]++;
  }
  
  // 找到最大频率
  int maxFreq = 0;
  for (const auto& [ch, count] : freq) {
    maxFreq = max(maxFreq, count);
  }
  
  // 桶：频率 -> 该频率的所有字符
  vector<vector<char>> buckets(maxFreq + 1);
  for (const auto& [ch, count] : freq) {
    buckets[count].push_back(ch);
  }
  
  // 从高频到低频构建结果
  string result;
  result.reserve(s.size());
  for (int f = maxFreq; f >= 1; --f) {
    for (char ch : buckets[f]) {
      result.append(f, ch);
    }
  }
  
  return result;
}

SortCharactersByFrequencySolution::SortCharactersByFrequencySolution() {
  setMetaInfo({.id = 451,
               .title = "Sort Characters By Frequency",
               .url = "https://leetcode.com/problems/sort-characters-by-frequency/"});
  registerStrategy("Hash + Sort", solution1);
  registerStrategy("Bucket Sort", solution2);
}

string SortCharactersByFrequencySolution::frequencySort(string s) {
  return getSolution()(s);
}

}  // namespace problem_451
}  // namespace leetcode
