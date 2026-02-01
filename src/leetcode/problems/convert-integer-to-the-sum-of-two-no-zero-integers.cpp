#include "leetcode/problems/convert-integer-to-the-sum-of-two-no-zero-integers.h"

namespace leetcode {
namespace problem_1317 {

// 辅助函数：检查数字是否包含0
static bool hasZero(int x) {
  while (x > 0) {
    if (x % 10 == 0) {
      return true;
    }
    x /= 10;
  }
  return false;
}

// 策略：枚举所有可能
// 时间复杂度: O(n * log(n)), 空间复杂度: O(1)
static vector<int> solution1(int n) {
  for (int i = 1; i < n; ++i) {
    int j = n - i;
    if (!hasZero(i) && !hasZero(j)) {
      return {i, j};
    }
  }
  return {};  // 根据题意不会执行到这里
}

ConvertIntegerToTheSumOfTwoNoZeroIntegersSolution::ConvertIntegerToTheSumOfTwoNoZeroIntegersSolution() {
  setMetaInfo({.id = 1317,
               .title = "Convert Integer to the Sum of Two No-Zero Integers",
               .url = "https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/"});
  registerStrategy("Enumeration", solution1);
}

vector<int> ConvertIntegerToTheSumOfTwoNoZeroIntegersSolution::getNoZeroIntegers(int n) {
  return getSolution()(n);
}

}  // namespace problem_1317
}  // namespace leetcode
