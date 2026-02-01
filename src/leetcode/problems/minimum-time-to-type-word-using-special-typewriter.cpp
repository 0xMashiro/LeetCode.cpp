#include "leetcode/problems/minimum-time-to-type-word-using-special-typewriter.h"

namespace leetcode {
namespace problem_1974 {

// 贪心算法：对于每个字符，选择顺时针或逆时针中距离较短的
// 每个字符需要 1 秒输入，移动距离为 min(|a-b|, 26-|a-b|)
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(string word) {
  int totalTime = 0;
  char current = 'a';
  
  for (char target : word) {
    // 计算顺时针和逆时针的距离
    int clockwise = (target - current + 26) % 26;
    int counterClockwise = (current - target + 26) % 26;
    
    // 选择较短的距离移动
    totalTime += std::min(clockwise, counterClockwise);
    
    // 输入字符需要 1 秒
    totalTime += 1;
    
    // 更新当前位置
    current = target;
  }
  
  return totalTime;
}

MinimumTimeToTypeWordUsingSpecialTypewriterSolution::MinimumTimeToTypeWordUsingSpecialTypewriterSolution() {
  setMetaInfo({.id = 1974,
               .title = "Minimum Time to Type Word Using Special Typewriter",
               .url = "https://leetcode.com/problems/minimum-time-to-type-word-using-special-typewriter/"});
  registerStrategy("Greedy", solution1);
}

int MinimumTimeToTypeWordUsingSpecialTypewriterSolution::minTimeToType(string word) {
  return getSolution()(word);
}

}  // namespace problem_1974
}  // namespace leetcode
