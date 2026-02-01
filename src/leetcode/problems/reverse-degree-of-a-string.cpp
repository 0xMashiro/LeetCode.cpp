#include "leetcode/problems/reverse-degree-of-a-string.h"

namespace leetcode {
namespace problem_3498 {

// 遍历字符串，计算每个字符的反向字母表位置乘以其字符串位置
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(string s) {
  int result = 0;
  const int n = s.size();
  for (int i = 0; i < n; ++i) {
    // 反向字母表位置: 'a'=26, 'b'=25, ..., 'z'=1
    int reversePos = 26 - (s[i] - 'a');
    // 字符串位置是 1-indexed
    result += reversePos * (i + 1);
  }
  return result;
}

ReverseDegreeOfAStringSolution::ReverseDegreeOfAStringSolution() {
  setMetaInfo({.id = 3498,
               .title = "Reverse Degree of a String",
               .url = "https://leetcode.com/problems/reverse-degree-of-a-string/"});
  registerStrategy("Linear Scan", solution1);
}

int ReverseDegreeOfAStringSolution::reverseDegree(string s) {
  return getSolution()(s);
}

}  // namespace problem_3498
}  // namespace leetcode
