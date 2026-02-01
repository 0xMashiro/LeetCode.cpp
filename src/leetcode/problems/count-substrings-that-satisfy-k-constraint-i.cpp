
#include "leetcode/problems/count-substrings-that-satisfy-k-constraint-i.h"

namespace leetcode {
namespace problem_3258 {

// 枚举所有子串，统计满足 k-constraint 的数量
// 时间复杂度: O(n²), 空间复杂度: O(1)
static int solution1(string s, int k) {
  const int n = s.size();
  int count = 0;
  
  for (int i = 0; i < n; ++i) {
    int zeros = 0, ones = 0;
    for (int j = i; j < n; ++j) {
      if (s[j] == '0') {
        ++zeros;
      } else {
        ++ones;
      }
      // 检查是否满足 k-constraint
      if (zeros <= k || ones <= k) {
        ++count;
      }
    }
  }
  
  return count;
}

CountSubstringsThatSatisfyKConstraintISolution::CountSubstringsThatSatisfyKConstraintISolution() {
  setMetaInfo({.id = 3258,
               .title = "Count Substrings That Satisfy K-Constraint I",
               .url = "https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-i/"});
  registerStrategy("Enumerate", solution1);
}

int CountSubstringsThatSatisfyKConstraintISolution::countKConstraintSubstrings(string s, int k) {
  return getSolution()(s, k);
}

}  // namespace problem_3258
}  // namespace leetcode
