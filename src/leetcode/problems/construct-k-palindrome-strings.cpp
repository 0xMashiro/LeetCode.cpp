
#include "leetcode/problems/construct-k-palindrome-strings.h"

namespace leetcode {
namespace problem_1400 {

// 统计奇数频次字符数量，判断可行性
// 时间复杂度: O(n), 空间复杂度: O(1)
static bool solution1(string s, int k) {
  int n = s.length();
  
  // k 不能超过字符串长度（每个回文串至少一个字符）
  if (k > n) {
    return false;
  }
  
  // 统计每个字符出现次数
  int count[26] = {0};
  for (char c : s) {
    count[c - 'a']++;
  }
  
  // 计算出现奇数次的字符个数
  int oddCount = 0;
  for (int i = 0; i < 26; i++) {
    if (count[i] % 2 == 1) {
      oddCount++;
    }
  }
  
  // 需要足够的回文串来容纳所有奇数频次字符
  // 同时 k 不能超过字符串长度（前面已判断）
  return oddCount <= k;
}

// 优化版本：使用位运算统计奇偶性
// 时间复杂度: O(n), 空间复杂度: O(1)
static bool solution2(string s, int k) {
  int n = s.length();
  
  if (k > n) {
    return false;
  }
  
  // 使用位掩码记录奇偶性
  int mask = 0;
  for (char c : s) {
    mask ^= (1 << (c - 'a'));
  }
  
  // 计算二进制中1的个数（即奇数频次字符个数）
  int oddCount = __builtin_popcount(mask);
  
  return oddCount <= k;
}

ConstructKPalindromeStringsSolution::ConstructKPalindromeStringsSolution() {
  setMetaInfo({
    .id = 1400,
    .title = "Construct K Palindrome Strings",
    .url = "https://leetcode.com/problems/construct-k-palindrome-strings/"
  });
  registerStrategy("Counting", solution1);
  registerStrategy("Bit Manipulation", solution2);
}

bool ConstructKPalindromeStringsSolution::canConstruct(string s, int k) {
  return getSolution()(s, k);
}

}  // namespace problem_1400
}  // namespace leetcode
