#include "leetcode/problems/divide-two-integers.h"

namespace leetcode {
namespace problem_29 {

/**
 * 思路：使用位移和减法模拟除法运算（快速幂思想）
 * 
 * 关键观察：
 * - dividend / divisor = quotient 意味着 dividend = divisor * quotient
 * - 我们可以找到最大的 k，使得 divisor * 2^k <= dividend
 * - 然后 dividend -= divisor * 2^k，quotient += 2^k，继续循环
 * 
 * 为了处理溢出：将被除数和除数都转换为负数处理
 * 因为负数范围是 [-2^31, 0]，正数范围是 [0, 2^31-1]
 * INT_MIN 转换为正数会溢出，但转换为负数不会
 * 
 * 时间复杂度: O(log^2 n)，最坏情况下需要进行 O(log n) 次外层循环，
 *           每次内层循环最多进行 O(log n) 次位移
 * 空间复杂度: O(1)
 */
static int solution1(int dividend, int divisor) {
  // 特殊情况：唯一会导致溢出的情况
  if (dividend == INT_MIN && divisor == -1) {
    return INT_MAX;
  }
  
  // 记录结果的符号
  bool negative = (dividend > 0) ^ (divisor > 0);
  
  // 将被除数和除数都转换为负数，避免溢出
  // 因为 -INT_MIN 会溢出，但 -INT_MAX 不会
  int a = dividend > 0 ? -dividend : dividend;
  int b = divisor > 0 ? -divisor : divisor;
  
  int result = 0;
  
  // 外层循环：当 a 的绝对值还大于等于 b 的绝对值时继续
  // a <= b 因为都是负数（绝对值大的数更小）
  while (a <= b) {
    int value = b;
    int quotient = 1;
    
    // 内层循环：找到最大的 value = b * 2^k，使得 value <= a（都是负数）
    // 即 |value| <= |a|，value 和 a 都是负数
    // 防止 value + value 溢出（变成正数），需要判断 value >= (INT_MIN >> 1)
    while (value >= (INT_MIN >> 1) && a <= value + value) {
      quotient += quotient;  // quotient *= 2
      value += value;        // value *= 2
    }
    
    result += quotient;
    a -= value;  // a 是负数，value 也是负数，所以 a -= value 相当于 a += |value|
  }
  
  return negative ? -result : result;
}

/**
 * 优化版本：使用 long long 避免溢出检查的复杂度
 * 时间复杂度: O(log n)
 * 空间复杂度: O(1)
 */
static int solution2(int dividend, int divisor) {
  // 特殊情况处理
  if (dividend == INT_MIN && divisor == -1) {
    return INT_MAX;
  }
  
  // 记录结果的符号
  bool negative = (dividend > 0) ^ (divisor > 0);
  
  // 使用 long long 避免溢出
  long long a = llabs((long long)dividend);
  long long b = llabs((long long)divisor);
  
  long long result = 0;
  
  // 从最大的 2^k 开始尝试
  for (int i = 31; i >= 0; i--) {
    if ((a >> i) >= b) {
      result += (1LL << i);
      a -= (b << i);
    }
  }
  
  result = negative ? -result : result;
  
  // 检查结果是否溢出
  if (result > INT_MAX) return INT_MAX;
  if (result < INT_MIN) return INT_MIN;
  
  return (int)result;
}

DivideTwoIntegersSolution::DivideTwoIntegersSolution() {
  setMetaInfo({.id = 29,
               .title = "Divide Two Integers",
               .url = "https://leetcode.com/problems/divide-two-integers/"});
  registerStrategy("Bit Manipulation + Subtraction", solution1);
  registerStrategy("Long Long Optimization", solution2);
}

int DivideTwoIntegersSolution::divide(int dividend, int divisor) {
  return getSolution()(dividend, divisor);
}

}  // namespace problem_29
}  // namespace leetcode
