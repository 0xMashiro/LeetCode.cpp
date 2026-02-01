#include "leetcode/problems/maximum-product-of-two-digits.h"

namespace leetcode {
namespace problem_3536 {

// 排序法：提取所有数字，排序后取最大的两个相乘
// 时间复杂度: O(d log d)，d 为数字位数（最多10位）
// 空间复杂度: O(d)
static int solution1(int n) {
  vector<int> digits;
  while (n > 0) {
    digits.push_back(n % 10);
    n /= 10;
  }
  sort(digits.begin(), digits.end());
  const int m = digits.size();
  return digits[m - 1] * digits[m - 2];
}

// 一次遍历：维护最大和次大值
// 时间复杂度: O(d)，d 为数字位数
// 空间复杂度: O(1)
static int solution2(int n) {
  int max1 = 0, max2 = 0;  // max1 >= max2
  while (n > 0) {
    int digit = n % 10;
    n /= 10;
    if (digit > max1) {
      max2 = max1;
      max1 = digit;
    } else if (digit > max2) {
      max2 = digit;
    }
  }
  return max1 * max2;
}

MaximumProductOfTwoDigitsSolution::MaximumProductOfTwoDigitsSolution() {
  setMetaInfo({.id = 3536,
               .title = "Maximum Product of Two Digits",
               .url = "https://leetcode.com/problems/maximum-product-of-two-digits/"});
  registerStrategy("Sorting", solution1);
  registerStrategy("One Pass", solution2);
}

int MaximumProductOfTwoDigitsSolution::maxProduct(int n) {
  return getSolution()(n);
}

}  // namespace problem_3536
}  // namespace leetcode
