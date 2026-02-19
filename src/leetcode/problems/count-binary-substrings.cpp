
#include "leetcode/problems/count-binary-substrings.h"

namespace leetcode {
namespace problem_696 {

// 分组计数法：将连续相同的字符分组，统计每组长度
// 对于相邻两组，可以形成 min(prev, curr) 个有效子串
// 时间复杂度: O(n), 空间复杂度: O(1)（如果只计数不分组存储）
static int solution1(string s) {
  int n = s.size();
  if (n < 2) return 0;
  
  int result = 0;
  int prev_count = 0;  // 前一组的连续字符数
  int curr_count = 1;  // 当前组的连续字符数（至少为1）
  
  for (int i = 1; i < n; ++i) {
    if (s[i] == s[i-1]) {
      // 仍在当前组
      curr_count++;
    } else {
      // 组切换，计算前一组和当前组能形成的子串数
      result += min(prev_count, curr_count);
      // 前一组变成当前组，当前组重新开始计数
      prev_count = curr_count;
      curr_count = 1;
    }
  }
  
  // 处理最后一组
  result += min(prev_count, curr_count);
  
  return result;
}

CountBinarySubstringsSolution::CountBinarySubstringsSolution() {
  setMetaInfo({.id = 696,
               .title = "Count Binary Substrings",
               .url = "https://leetcode.com/problems/count-binary-substrings/"});
  registerStrategy("Group Count", solution1);
}

int CountBinarySubstringsSolution::countBinarySubstrings(string s) {
  return getSolution()(s);
}

}  // namespace problem_696
}  // namespace leetcode
