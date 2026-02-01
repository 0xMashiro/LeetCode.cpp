#include "leetcode/problems/longest-substring-of-all-vowels-in-order.h"

namespace leetcode {
namespace problem_1839 {

/**
 * 思路：滑动窗口
 * 1. 遍历字符串，维护当前窗口的起始位置
 * 2. 如果当前字符 < 前一个字符，顺序被打破，重新开始窗口
 * 3. 使用位掩码记录当前窗口包含的元音类型
 * 4. 当包含所有5个元音时，更新最大长度
 * 
 * 时间复杂度: O(n), 空间复杂度: O(1)
 */
static int solution(string word) {
  const int n = word.size();
  if (n < 5) return 0;
  
  int maxLen = 0;
  int start = 0;  // 当前窗口的起始位置
  int vowelMask = 0;  // 位掩码，记录当前窗口包含的元音
  
  // 将元音映射到对应的位
  auto getVowelBit = [](char c) -> int {
    switch (c) {
      case 'a': return 1 << 0;  // 第0位
      case 'e': return 1 << 1;  // 第1位
      case 'i': return 1 << 2;  // 第2位
      case 'o': return 1 << 3;  // 第3位
      case 'u': return 1 << 4;  // 第4位
      default: return 0;
    }
  };
  
  for (int i = 0; i < n; ++i) {
    // 如果当前字符 < 前一个字符，顺序被打破，重新开始
    if (i > 0 && word[i] < word[i - 1]) {
      start = i;
      vowelMask = 0;
    }
    
    // 添加当前元音到掩码
    vowelMask |= getVowelBit(word[i]);
    
    // 检查是否包含所有5个元音 (0b11111 = 31)
    if (vowelMask == 31) {
      maxLen = max(maxLen, i - start + 1);
    }
  }
  
  return maxLen;
}

LongestSubstringOfAllVowelsInOrderSolution::LongestSubstringOfAllVowelsInOrderSolution() {
  setMetaInfo({.id = 1839,
               .title = "Longest Substring Of All Vowels in Order",
               .url = "https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/"});
  registerStrategy("Sliding Window", solution);
}

int LongestSubstringOfAllVowelsInOrderSolution::longestBeautifulSubstring(string word) {
  return getSolution()(word);
}

}  // namespace problem_1839
}  // namespace leetcode
