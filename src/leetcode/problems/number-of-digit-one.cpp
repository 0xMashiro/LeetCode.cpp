#include "leetcode/problems/number-of-digit-one.h"

namespace leetcode {
namespace problem_233 {

// 数位统计法：逐位计算每一位上数字 1 出现的次数
// 时间复杂度: O(log10(n))，最多遍历 10 位
// 空间复杂度: O(1)
static int solution1(int n) {
  long long count = 0;  // 使用 long long 防止溢出
  long long factor = 1;  // 当前位的位权（1, 10, 100, ...）
  
  while (factor <= n) {
    long long higher = n / (factor * 10);  // 高位数字
    long long current = (n / factor) % 10;  // 当前位数字
    long long lower = n % factor;  // 低位数字
    
    if (current > 1) {
      // 当前位 > 1，高位可以取 0~higher，共 (higher+1) 种
      count += (higher + 1) * factor;
    } else if (current == 1) {
      // 当前位 == 1，高位取 0~higher-1 时有 factor 种低位
      // 高位取 higher 时，低位可以取 0~lower，共 lower+1 种
      count += higher * factor + lower + 1;
    } else {
      // 当前位 == 0，高位只能取 0~higher-1
      count += higher * factor;
    }
    
    factor *= 10;
  }
  
  return static_cast<int>(count);
}

NumberOfDigitOneSolution::NumberOfDigitOneSolution() {
  setMetaInfo({.id = 233,
               .title = "Number of Digit One",
               .url = "https://leetcode.com/problems/number-of-digit-one/"});
  registerStrategy("Digit Counting", solution1);
}

int NumberOfDigitOneSolution::countDigitOne(int n) {
  return getSolution()(n);
}

}  // namespace problem_233
}  // namespace leetcode
