#include "leetcode/problems/consecutive-characters.h"

namespace leetcode {
namespace problem_1446 {

// 一次遍历：统计连续相同字符的最大长度
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(std::string s) {
  const int n = s.length();
  if (n == 0) return 0;
  
  int maxPower = 1;      // 最大连续长度
  int currentPower = 1;  // 当前连续长度
  
  for (int i = 1; i < n; ++i) {
    if (s[i] == s[i - 1]) {
      // 连续相同字符，增加当前长度
      ++currentPower;
    } else {
      // 字符不同，重置当前长度
      currentPower = 1;
    }
    // 更新最大长度
    maxPower = std::max(maxPower, currentPower);
  }
  
  return maxPower;
}

ConsecutiveCharactersSolution::ConsecutiveCharactersSolution() {
  setMetaInfo({.id = 1446,
               .title = "Consecutive Characters",
               .url = "https://leetcode.com/problems/consecutive-characters/"});
  registerStrategy("One Pass", solution1);
}

int ConsecutiveCharactersSolution::maxPower(std::string s) {
  return getSolution()(s);
}

}  // namespace problem_1446
}  // namespace leetcode
