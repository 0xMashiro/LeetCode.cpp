#include "leetcode/problems/count-good-numbers.h"

namespace leetcode {
namespace problem_1922 {

// 常量定义
static constexpr int MOD = 1'000'000'007;

/**
 * 快速幂算法（二进制幂）
 * 计算 (base^exp) % mod
 * 时间复杂度: O(log exp)
 * 
 * 原理：将指数表示为二进制，通过平方逐步计算
 * 例如：a^13 = a^(1101)_2 = a^8 × a^4 × a^1
 */
static long long fastPower(long long base, long long exp, int mod) {
  long long result = 1;
  base %= mod;
  
  while (exp > 0) {
    // 如果当前二进制位为 1，乘以对应的幂
    if (exp & 1) {
      result = (result * base) % mod;
    }
    // 底数平方，准备下一位
    base = (base * base) % mod;
    // 指数右移一位
    exp >>= 1;
  }
  
  return result;
}

/**
 * 计算好数字字符串的数量
 * 
 * 分析：
 * - 偶数索引位置（0, 2, 4...）：可选 {0, 2, 4, 6, 8} = 5 种
 * - 奇数索引位置（1, 3, 5...）：可选 {2, 3, 5, 7} = 4 种
 * - 长度为 n 时：偶数位置数 = (n+1)/2，奇数位置数 = n/2
 * 
 * 答案 = 5^((n+1)/2) × 4^(n/2) % MOD
 * 
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1)
 */
static int solution(long long n) {
  // 计算偶数位置和奇数位置的数量
  long long evenPositions = (n + 1) / 2;  // 索引 0, 2, 4...
  long long oddPositions = n / 2;          // 索引 1, 3, 5...
  
  // 计算 5^evenPositions × 4^oddPositions % MOD
  long long pow5 = fastPower(5, evenPositions, MOD);
  long long pow4 = fastPower(4, oddPositions, MOD);
  
  return static_cast<int>((pow5 * pow4) % MOD);
}

CountGoodNumbersSolution::CountGoodNumbersSolution() {
  setMetaInfo({
    .id = 1922,
    .title = "Count Good Numbers",
    .url = "https://leetcode.com/problems/count-good-numbers/"
  });
  registerStrategy("Fast Power", solution);
}

int CountGoodNumbersSolution::countGoodNumbers(long long n) {
  return getSolution()(n);
}

}  // namespace problem_1922
}  // namespace leetcode
