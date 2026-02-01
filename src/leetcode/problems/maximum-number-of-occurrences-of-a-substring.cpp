#include "leetcode/problems/maximum-number-of-occurrences-of-a-substring.h"

namespace leetcode {
namespace problem_1297 {

/**
 * @brief 滑动窗口 + 哈希表
 * @details 关键优化：只需要考虑 minSize 长度的子串
 *          因为如果长度为 L 的子串出现 k 次，它的子串至少也出现 k 次
 *          所以长度越短，出现次数越多
 *          时间复杂度: O(n × minSize), 空间复杂度: O(n × minSize)
 */
static int solution1(string& s, int maxLetters, int minSize, int maxSize) {
  const int n = s.size();
  int maxFreq = 0;
  
  // 只需要枚举 minSize 长度的子串
  // 统计每个满足条件的子串的出现次数
  unordered_map<string, int> substringCount;
  
  // 字符频率数组
  int charCount[26] = {0};
  int uniqueChars = 0;
  
  // 初始化第一个窗口
  for (int i = 0; i < minSize && i < n; ++i) {
    int idx = s[i] - 'a';
    if (charCount[idx] == 0) {
      ++uniqueChars;
    }
    ++charCount[idx];
  }
  
  // 检查第一个窗口
  if (uniqueChars <= maxLetters) {
    string sub = s.substr(0, minSize);
    ++substringCount[sub];
    maxFreq = 1;
  }
  
  // 滑动窗口
  for (int i = minSize; i < n; ++i) {
    // 移除左边字符
    int leftIdx = s[i - minSize] - 'a';
    --charCount[leftIdx];
    if (charCount[leftIdx] == 0) {
      --uniqueChars;
    }
    
    // 添加右边字符
    int rightIdx = s[i] - 'a';
    if (charCount[rightIdx] == 0) {
      ++uniqueChars;
    }
    ++charCount[rightIdx];
    
    // 检查当前窗口是否满足条件
    if (uniqueChars <= maxLetters) {
      string sub = s.substr(i - minSize + 1, minSize);
      ++substringCount[sub];
      maxFreq = max(maxFreq, substringCount[sub]);
    }
  }
  
  return maxFreq;
}

MaximumNumberOfOccurrencesOfASubstringSolution::MaximumNumberOfOccurrencesOfASubstringSolution() {
  setMetaInfo({
    .id = 1297,
    .title = "Maximum Number of Occurrences of a Substring",
    .url = "https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/"
  });
  registerStrategy("Sliding Window + HashMap", solution1);
}

int MaximumNumberOfOccurrencesOfASubstringSolution::maxFreq(string s, int maxLetters, int minSize, int maxSize) {
  return getSolution()(s, maxLetters, minSize, maxSize);
}

}  // namespace problem_1297
}  // namespace leetcode
