#include "leetcode/problems/binary-number-with-alternating-bits.h"

namespace leetcode {
namespace problem_693 {

// 逐位检查法
// 时间复杂度: O(log n), 空间复杂度: O(1)
static bool solution1(int n) {
  int prev = n & 1;  // 获取最低位
  n >>= 1;
  while (n > 0) {
    int curr = n & 1;  // 获取当前最低位
    if (curr == prev) return false;
    prev = curr;
    n >>= 1;
  }
  return true;
}

// 数学技巧法
// 如果 n 有交替位，则 n ^ (n >> 1) 的结果全为1（形如 111...111）
// 全为1的数加1后会变成2的幂次，即 (n ^ (n >> 1) + 1) & (n ^ (n >> 1)) == 0
// 时间复杂度: O(1), 空间复杂度: O(1)
static bool solution2(int n) {
  unsigned int x = n ^ (n >> 1);
  return (x & (x + 1)) == 0;
}

BinaryNumberWithAlternatingBitsSolution::BinaryNumberWithAlternatingBitsSolution() {
  setMetaInfo({.id = 693,
               .title = "Binary Number with Alternating Bits",
               .url = "https://leetcode.com/problems/binary-number-with-alternating-bits/"});
  registerStrategy("Bit by Bit Check", solution1);
  registerStrategy("Math Trick", solution2);
}

bool BinaryNumberWithAlternatingBitsSolution::hasAlternatingBits(int n) {
  return getSolution()(n);
}

}  // namespace problem_693
}  // namespace leetcode
