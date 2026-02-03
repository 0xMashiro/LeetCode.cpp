#include "leetcode/problems/minimum-length-of-string-after-operations.h"

namespace leetcode {
namespace problem_3223 {

/**
 * 统计每个字符出现次数
 * 对于出现 count 次的字符：
 * - count <= 2：保留 count 个（无法操作或操作后无收益）
 * - count >= 3：最终剩下 1 个（count 为奇数）或 2 个（count 为偶数）
 * 
 * 时间复杂度: O(n)，其中 n 为字符串长度
 * 空间复杂度: O(1)，只需要 26 个计数器
 */
static int solution1(string s) {
  vector<int> count(26, 0);
  
  // 统计每个字符出现次数
  for (char c : s) {
    count[c - 'a']++;
  }
  
  int result = 0;
  for (int c : count) {
    if (c == 0) continue;
    // count <= 2 时保留原数，count > 2 时保留 1(奇数) 或 2(偶数)
    if (c <= 2) {
      result += c;
    } else {
      result += (c % 2 == 0) ? 2 : 1;
    }
  }
  
  return result;
}

MinimumLengthOfStringAfterOperationsSolution::MinimumLengthOfStringAfterOperationsSolution() {
  setMetaInfo({
    .id = 3223,
    .title = "Minimum Length of String After Operations",
    .url = "https://leetcode.com/problems/minimum-length-of-string-after-operations/"
  });
  registerStrategy("Counting", solution1);
}

int MinimumLengthOfStringAfterOperationsSolution::minimumLength(string s) {
  return getSolution()(s);
}

}  // namespace problem_3223
}  // namespace leetcode
