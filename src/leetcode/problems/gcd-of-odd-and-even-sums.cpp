
#include "leetcode/problems/gcd-of-odd-and-even-sums.h"

namespace leetcode {
namespace problem_3658 {

// 数学方法：
// 前 n 个奇数之和 = 1 + 3 + ... + (2n-1) = n²
// 前 n 个偶数之和 = 2 + 4 + ... + 2n = n(n+1)
// GCD(n², n(n+1)) = GCD(n², n) = n
// 时间复杂度: O(1), 空间复杂度: O(1)
static int solution1(int n) {
  return n;
}

// 直接计算法（验证用）
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(int n) {
  long long sumOdd = 0, sumEven = 0;
  for (int i = 1; i <= n; ++i) {
    sumOdd += 2 * i - 1;  // 第 i 个奇数
    sumEven += 2 * i;     // 第 i 个偶数
  }
  return std::gcd(sumOdd, sumEven);
}

GcdOfOddAndEvenSumsSolution::GcdOfOddAndEvenSumsSolution() {
  setMetaInfo({.id = 3658,
               .title = "GCD of Odd and Even Sums",
               .url = "https://leetcode.com/problems/gcd-of-odd-and-even-sums/"});
  registerStrategy("Math Formula", solution1);
  registerStrategy("Direct Calculation", solution2);
}

int GcdOfOddAndEvenSumsSolution::gcdOfOddEvenSums(int n) {
  return getSolution()(n);
}

}  // namespace problem_3658
}  // namespace leetcode
