#include "leetcode/problems/minimum-element-after-replacement-with-digit-sum.h"

namespace leetcode {
namespace problem_3300 {

// 计算一个整数的各位数字之和
static int digitSum(int x) {
  int sum = 0;
  while (x > 0) {
    sum += x % 10;
    x /= 10;
  }
  return sum;
}

// 解法1：即时计算法（朴素）
// 遍历数组，对每个数即时计算 digit sum，同时维护最小值
// 时间复杂度: O(n * log10(maxVal)) = O(n * 5)，空间复杂度: O(1)
static int solution1(vector<int>& nums) {
  int minVal = INT_MAX;
  for (int x : nums) {
    int s = digitSum(x);
    if (s < minVal) minVal = s;
  }
  return minVal;
}

// 解法2：预计算查表法
// 由于 nums[i] 范围固定为 [1, 10^4]，预先计算所有可能数的 digit sum 存入数组
// 遍历 nums 时直接查表，避免重复计算
// 时间复杂度: O(maxVal + n)，空间复杂度: O(maxVal)
static int solution2(vector<int>& nums) {
  // 预计算 [0, 10000] 的 digit sum
  static const int MAX_VAL = 10000;
  static int precomputed[MAX_VAL + 1];
  static bool initialized = false;
  if (!initialized) {
    for (int i = 0; i <= MAX_VAL; ++i) {
      precomputed[i] = digitSum(i);
    }
    initialized = true;
  }

  int minVal = INT_MAX;
  for (int x : nums) {
    int s = precomputed[x];
    if (s < minVal) minVal = s;
  }
  return minVal;
}

MinimumElementAfterReplacementWithDigitSumSolution::MinimumElementAfterReplacementWithDigitSumSolution() {
  setMetaInfo({.id = 3300,
               .title = "Minimum Element After Replacement With Digit Sum",
               .url = "https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/"});
  registerStrategy("On-the-fly Digit Sum", solution1);
  registerStrategy("Precomputed Lookup", solution2);
}

int MinimumElementAfterReplacementWithDigitSumSolution::minElement(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3300
}  // namespace leetcode
