#include "leetcode/problems/number-of-1-bits.h"

namespace leetcode {
namespace problem_191 {

// 逐位检查：遍历 32 位，检查每一位是否为 1
// 时间复杂度: O(32) = O(1), 空间复杂度: O(1)
static int solution1(int n) {
  int count = 0;
  for (int i = 0; i < 32; ++i) {
    count += (n >> i) & 1;
  }
  return count;
}

// Brian Kernighan 算法：n & (n-1) 可以消除最低位的 1
// 时间复杂度: O(k), k 为 1 的个数，最坏 O(32) = O(1)
// 空间复杂度: O(1)
static int solution2(int n) {
  int count = 0;
  while (n) {
    n &= n - 1;  // 消除最低位的 1
    ++count;
  }
  return count;
}

// 查表法（适用于频繁调用）：每 4 位查表
// 时间复杂度: O(1), 空间复杂度: O(1)
static int solution3(int n) {
  static const int table[16] = {0, 1, 1, 2, 1, 2, 2, 3, 
                                 1, 2, 2, 3, 2, 3, 3, 4};
  return table[n & 0xF] + 
         table[(n >> 4) & 0xF] + 
         table[(n >> 8) & 0xF] + 
         table[(n >> 12) & 0xF] + 
         table[(n >> 16) & 0xF] + 
         table[(n >> 20) & 0xF] + 
         table[(n >> 24) & 0xF] + 
         table[(n >> 28) & 0xF];
}

NumberOf1BitsSolution::NumberOf1BitsSolution() {
  setMetaInfo({.id = 191,
               .title = "Number of 1 Bits",
               .url = "https://leetcode.com/problems/number-of-1-bits/"});
  registerStrategy("Bit by Bit", solution1);
  registerStrategy("Brian Kernighan", solution2);
  registerStrategy("Lookup Table", solution3);
}

int NumberOf1BitsSolution::hammingWeight(int n) {
  return getSolution()(n);
}

}  // namespace problem_191
}  // namespace leetcode
