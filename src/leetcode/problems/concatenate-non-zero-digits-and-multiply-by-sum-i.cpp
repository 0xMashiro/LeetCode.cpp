#include "leetcode/problems/concatenate-non-zero-digits-and-multiply-by-sum-i.h"

#include <algorithm>
#include <string>

namespace leetcode {
namespace problem_3754 {

// 提取所有非零数字拼接成 x，同时累加数字和 sum，返回 x * sum
// 时间复杂度: O(log n), 空间复杂度: O(log n)
static long long solution1(int n) {
  if (n == 0) return 0;

  std::string digits;
  int sum = 0;
  int temp = n;
  while (temp > 0) {
    int d = temp % 10;
    if (d != 0) {
      digits.push_back('0' + d);
      sum += d;
    }
    temp /= 10;
  }

  if (digits.empty()) return 0;

  // 从低位到高位收集，需要反转恢复原序
  std::reverse(digits.begin(), digits.end());
  long long x = std::stoll(digits);
  return x * sum;
}

ConcatenateNonZeroDigitsAndMultiplyBySumISolution::ConcatenateNonZeroDigitsAndMultiplyBySumISolution() {
  setMetaInfo({.id = 3754,
               .title = "Concatenate Non-Zero Digits and Multiply by Sum I",
               .url = "https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/"});
  registerStrategy({.name = "Extract and Build",
                    .expected = "Accepted",
                    .time_complexity = "O(log n)",
                    .space_complexity = "O(log n)",
                    .tags = {"Math"}},
                   solution1);
}

long long ConcatenateNonZeroDigitsAndMultiplyBySumISolution::sumAndMultiply(int n) {
  return getSolution()(n);
}

}  // namespace problem_3754
}  // namespace leetcode
