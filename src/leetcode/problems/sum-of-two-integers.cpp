#include "leetcode/problems/sum-of-two-integers.h"

namespace leetcode {
namespace problem_371 {

// 位运算实现加法
// 思路：
// 1. 异或运算 ^ 得到无进位的和
// 2. 与运算 & 得到进位位置，左移一位得到实际进位值
// 3. 重复直到进位为0
// 时间复杂度: O(1)，最多32次迭代（int的位数）
// 空间复杂度: O(1)
static int solution1(int a, int b) {
  while (b != 0) {
    // 计算无进位的和
    int sum = a ^ b;
    // 计算进位（注意：C++中需要转为unsigned避免溢出）
    int carry = (a & b) << 1;
    a = sum;
    b = carry;
  }
  return a;
}

SumOfTwoIntegersSolution::SumOfTwoIntegersSolution() {
  setMetaInfo({.id = 371,
               .title = "Sum of Two Integers",
               .url = "https://leetcode.com/problems/sum-of-two-integers/"});
  registerStrategy("Bit Manipulation", solution1);
}

int SumOfTwoIntegersSolution::getSum(int a, int b) {
  return getSolution()(a, b);
}

}  // namespace problem_371
}  // namespace leetcode
