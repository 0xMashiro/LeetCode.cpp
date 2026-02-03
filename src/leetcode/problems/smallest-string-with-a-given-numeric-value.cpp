#include "leetcode/problems/smallest-string-with-a-given-numeric-value.h"

namespace leetcode {
namespace problem_1663 {

// 贪心算法：从后往前构造，让前面的字符尽可能小
// 时间复杂度: O(n), 空间复杂度: O(n) 用于返回结果
static string solution1(int n, int k) {
  string result(n, 'a');  // 初始化为全'a'
  
  // 从后往前填充
  int i = n - 1;
  while (k > 0 && i >= 0) {
    // 后面还有 i 个位置，每个位置最小值为1
    // 所以当前位置可以放的最大值为 k - i
    int maxVal = k - i;
    // 当前位置实际放的值（不能超过26）
    int val = std::min(26, maxVal);
    // 设置当前字符（'a'对应1，所以要减1）
    result[i] = 'a' + val - 1;
    // 更新 k
    k -= val;
    i--;
  }
  
  return result;
}

// 更简洁的写法：直接计算每个位置的值
static string solution2(int n, int k) {
  string result;
  result.reserve(n);
  
  for (int i = n - 1; i >= 0; i--) {
    // 剩余位置（包括当前）共 i+1 个，后面 i 个位置最小需要 i
    // 当前位置最大可以取 min(26, k - i)
    int val = std::min(26, k - i);
    result.push_back('a' + val - 1);
    k -= val;
  }
  
  // 需要反转，因为我们是从后往前构造的
  std::reverse(result.begin(), result.end());
  return result;
}

SmallestStringWithAGivenNumericValueSolution::SmallestStringWithAGivenNumericValueSolution() {
  setMetaInfo({.id = 1663,
               .title = "Smallest String With A Given Numeric Value",
               .url = "https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/"});
  registerStrategy("Greedy Forward", solution1);
  registerStrategy("Greedy Reverse", solution2);
}

string SmallestStringWithAGivenNumericValueSolution::getSmallestString(int n, int k) {
  return getSolution()(n, k);
}

}  // namespace problem_1663
}  // namespace leetcode
