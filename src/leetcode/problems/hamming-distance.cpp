#include "leetcode/problems/hamming-distance.h"

namespace leetcode {
namespace problem_461 {

// Brian Kernighan 算法：每次消除最低位的1
// 时间复杂度: O(1) - 最多32次迭代
// 空间复杂度: O(1)
static int solution1(int x, int y) {
  int xor_val = x ^ y;
  int distance = 0;
  while (xor_val != 0) {
    xor_val &= xor_val - 1;  // 消除最低位的1
    ++distance;
  }
  return distance;
}

// GCC 内置函数：__builtin_popcount
// 时间复杂度: O(1), 通常编译为高效的CPU指令
// 空间复杂度: O(1)
static int solution2(int x, int y) {
  return __builtin_popcount(x ^ y);
}

// 逐位检查：遍历32位
// 时间复杂度: O(32) = O(1)
// 空间复杂度: O(1)
static int solution3(int x, int y) {
  int xor_val = x ^ y;
  int distance = 0;
  for (int i = 0; i < 32; ++i) {
    distance += (xor_val >> i) & 1;
  }
  return distance;
}

HammingDistanceSolution::HammingDistanceSolution() {
  setMetaInfo({.id = 461,
               .title = "Hamming Distance",
               .url = "https://leetcode.com/problems/hamming-distance/"});
  registerStrategy("Brian Kernighan", solution1);
  registerStrategy("Builtin Popcount", solution2);
  registerStrategy("Bit by Bit", solution3);
}

int HammingDistanceSolution::hammingDistance(int x, int y) {
  return getSolution()(x, y);
}

}  // namespace problem_461
}  // namespace leetcode
