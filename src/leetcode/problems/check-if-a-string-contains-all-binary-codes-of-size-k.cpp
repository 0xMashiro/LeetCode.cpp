
#include "leetcode/problems/check-if-a-string-contains-all-binary-codes-of-size-k.h"

namespace leetcode {
namespace problem_1461 {

// 滑动窗口 + 位运算 + 哈希集合
// 时间复杂度: O(n), 空间复杂度: O(2^k)
static bool solution1(string s, int k) {
  const int n = s.size();
  const int total = 1 << k;  // 2^k
  
  // 剪枝：字符串长度不足以包含所有子串
  if (n < k + total - 1) {
    return false;
  }
  
  unordered_set<int> seen;
  int mask = total - 1;  // k 个 1，用于取低 k 位
  int num = 0;
  
  // 初始化窗口
  for (int i = 0; i < k; ++i) {
    num = (num << 1) | (s[i] - '0');
  }
  seen.insert(num);
  
  // 滑动窗口
  for (int i = k; i < n; ++i) {
    // 去掉最高位，加入新位
    num = ((num << 1) & mask) | (s[i] - '0');
    seen.insert(num);
    // 提前退出：如果已经找到所有子串
    if (seen.size() == total) {
      return true;
    }
  }
  
  return seen.size() == total;
}

// 使用 vector<bool> 替代 unordered_set，空间更优
// 时间复杂度: O(n), 空间复杂度: O(2^k)
static bool solution2(string s, int k) {
  const int n = s.size();
  const int total = 1 << k;  // 2^k
  
  // 剪枝
  if (n < k + total - 1) {
    return false;
  }
  
  vector<bool> seen(total, false);
  int count = 0;
  int mask = total - 1;
  int num = 0;
  
  // 初始化窗口
  for (int i = 0; i < k; ++i) {
    num = (num << 1) | (s[i] - '0');
  }
  seen[num] = true;
  count = 1;
  
  // 滑动窗口
  for (int i = k; i < n; ++i) {
    num = ((num << 1) & mask) | (s[i] - '0');
    if (!seen[num]) {
      seen[num] = true;
      ++count;
      if (count == total) {
        return true;
      }
    }
  }
  
  return count == total;
}

CheckIfAStringContainsAllBinaryCodesOfSizeKSolution::CheckIfAStringContainsAllBinaryCodesOfSizeKSolution() {
  setMetaInfo({.id = 1461,
               .title = "Check If a String Contains All Binary Codes of Size K",
               .url = "https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/"});
  registerStrategy("Sliding Window + HashSet", solution1);
  registerStrategy("Sliding Window + Vector", solution2);
}

bool CheckIfAStringContainsAllBinaryCodesOfSizeKSolution::hasAllCodes(string s, int k) {
  return getSolution()(s, k);
}

}  // namespace problem_1461
}  // namespace leetcode
