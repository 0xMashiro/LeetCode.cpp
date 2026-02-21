
#include "leetcode/problems/prime-number-of-set-bits-in-binary-representation.h"

namespace leetcode {
namespace problem_762 {

// 判断是否为素数（只处理小数字，因为 set bits 最多约 20 个）
static bool isPrime(int n) {
  if (n < 2) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

// 遍历每个数字，统计二进制中素数个 1 的数字个数
// 时间复杂度: O((right - left + 1) * log(right))，空间复杂度: O(1)
static int solution1(int left, int right) {
  int count = 0;
  for (int num = left; num <= right; ++num) {
    int setBits = __builtin_popcount(num);
    if (isPrime(setBits)) {
      ++count;
    }
  }
  return count;
}

// 使用位运算优化版本
// 时间复杂度: O((right - left + 1) * log(right))，空间复杂度: O(1)
static int solution2(int left, int right) {
  int count = 0;
  for (int num = left; num <= right; ++num) {
    int n = num;
    int setBits = 0;
    while (n) {
      setBits += (n & 1);
      n >>= 1;
    }
    if (isPrime(setBits)) {
      ++count;
    }
  }
  return count;
}

// 使用打表优化素数判断（set bits 最多约 20 个）
// 时间复杂度: O(right - left + 1)，空间复杂度: O(1)
static int solution3(int left, int right) {
  // 1-20 中的素数集合：2, 3, 5, 7, 11, 13, 17, 19
  // 使用位掩码表示：第 i 位为 1 表示 i 是素数
  const int primeMask = (1 << 2) | (1 << 3) | (1 << 5) | (1 << 7) | 
                        (1 << 11) | (1 << 13) | (1 << 17) | (1 << 19);
  int count = 0;
  for (int num = left; num <= right; ++num) {
    int setBits = __builtin_popcount(num);
    if (primeMask & (1 << setBits)) {
      ++count;
    }
  }
  return count;
}

PrimeNumberOfSetBitsInBinaryRepresentationSolution::PrimeNumberOfSetBitsInBinaryRepresentationSolution() {
  setMetaInfo({.id = 762,
               .title = "Prime Number of Set Bits in Binary Representation",
               .url = "https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/"});
  registerStrategy("Builtin Popcount", solution1);
  registerStrategy("Bit Manipulation", solution2);
  registerStrategy("Prime Mask", solution3);
}

int PrimeNumberOfSetBitsInBinaryRepresentationSolution::countPrimeSetBits(int left, int right) {
  return getSolution()(left, right);
}

}  // namespace problem_762
}  // namespace leetcode
