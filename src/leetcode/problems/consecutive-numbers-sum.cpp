#include "leetcode/problems/consecutive-numbers-sum.h"

namespace leetcode {
namespace problem_829 {

// 数学方法：枚举 k（连续整数的个数）
// 推导：n = a + (a+1) + ... + (a+k-1) = k*a + k*(k-1)/2
// 所以：k*a = n - k*(k-1)/2
// 需要满足：n - k*(k-1)/2 > 0 且能被 k 整除
// 时间复杂度: O(sqrt(n)), 空间复杂度: O(1)
static int solution1(int n) {
  int count = 0;
  // k*(k-1)/2 < n => k^2 < 2n => k < sqrt(2n)
  // 枚举 k 从 1 开始
  for (int k = 1; k * (k + 1) / 2 <= n; ++k) {
    // n - k*(k-1)/2 必须能被 k 整除
    int remainder = n - k * (k - 1) / 2;
    if (remainder > 0 && remainder % k == 0) {
      ++count;
    }
  }
  return count;
}

ConsecutiveNumbersSumSolution::ConsecutiveNumbersSumSolution() {
  setMetaInfo({.id = 829,
               .title = "Consecutive Numbers Sum",
               .url = "https://leetcode.com/problems/consecutive-numbers-sum/"});
  registerStrategy("Math - Enum k", solution1);
}

int ConsecutiveNumbersSumSolution::consecutiveNumbersSum(int n) {
  return getSolution()(n);
}

}  // namespace problem_829
}  // namespace leetcode
