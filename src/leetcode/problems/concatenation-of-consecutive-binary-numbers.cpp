
#include "leetcode/problems/concatenation-of-consecutive-binary-numbers.h"

namespace leetcode {
namespace problem_1680 {

// 迭代计算：每次将当前结果左移 k 位（k 为 i 的二进制位数），然后加上 i
// 时间复杂度: O(n log n), 空间复杂度: O(1)
static int solution1(int n) {
  const int MOD = 1000000007;
  long long result = 0;
  
  for (int i = 1; i <= n; ++i) {
    // 计算 i 的二进制位数
    int bits = 0;
    int temp = i;
    while (temp > 0) {
      bits++;
      temp >>= 1;
    }
    // 左移 bits 位相当于乘以 2^bits，然后加上 i
    result = ((result << bits) + i) % MOD;
  }
  
  return static_cast<int>(result);
}

// 优化版本：利用前导零计算位数，避免循环
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(int n) {
  const int MOD = 1000000007;
  long long result = 0;
  
  for (int i = 1; i <= n; ++i) {
    // 使用 __builtin_clz 计算前导零个数，从而得到位数
    // __builtin_clz(0) 是未定义行为，但 i >= 1
    int bits = 32 - __builtin_clz(i);
    result = ((result << bits) + i) % MOD;
  }
  
  return static_cast<int>(result);
}

// 进一步优化：当 i 是 2 的幂次时，位数增加 1
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution3(int n) {
  const int MOD = 1000000007;
  long long result = 0;
  int bits = 0;
  
  for (int i = 1; i <= n; ++i) {
    // 如果 i 是 2 的幂次，二进制位数增加 1
    // 判断方法：i & (i - 1) == 0 表示 i 是 2 的幂次
    if ((i & (i - 1)) == 0) {
      bits++;
    }
    result = ((result << bits) + i) % MOD;
  }
  
  return static_cast<int>(result);
}

ConcatenationOfConsecutiveBinaryNumbersSolution::ConcatenationOfConsecutiveBinaryNumbersSolution() {
  setMetaInfo({.id = 1680,
               .title = "Concatenation of Consecutive Binary Numbers",
               .url = "https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/"});
  registerStrategy("Iterative", solution1);
  registerStrategy("Builtin Clz", solution2);
  registerStrategy("Power of Two Check", solution3);
}

int ConcatenationOfConsecutiveBinaryNumbersSolution::concatenatedBinary(int n) {
  return getSolution()(n);
}

}  // namespace problem_1680
}  // namespace leetcode
