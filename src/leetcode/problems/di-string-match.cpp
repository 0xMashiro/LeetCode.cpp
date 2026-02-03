#include "leetcode/problems/di-string-match.h"

namespace leetcode {
namespace problem_942 {

// 双指针贪心：
// - 遇到 'I'，放置当前最小值
// - 遇到 'D'，放置当前最大值
// 时间复杂度: O(n), 空间复杂度: O(1)（不包括返回数组）
static vector<int> solution(string s) {
  int n = s.length();
  vector<int> perm;
  perm.reserve(n + 1);
  
  int low = 0, high = n;
  
  for (char c : s) {
    if (c == 'I') {
      perm.push_back(low++);
    } else {  // c == 'D'
      perm.push_back(high--);
    }
  }
  
  // 放置最后一个值
  perm.push_back(low);
  
  return perm;
}

DiStringMatchSolution::DiStringMatchSolution() {
  setMetaInfo({.id = 942,
               .title = "DI String Match",
               .url = "https://leetcode.com/problems/di-string-match/"});
  registerStrategy("Two Pointer Greedy", solution);
}

vector<int> DiStringMatchSolution::diStringMatch(string s) {
  return getSolution()(s);
}

}  // namespace problem_942
}  // namespace leetcode
