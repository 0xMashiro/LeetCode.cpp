#include "leetcode/problems/number-of-different-subsequences-gcds.h"

namespace leetcode {
namespace problem_1819 {

// 核心思路：枚举所有可能的 GCD 值
// 对于候选值 g，如果数组中存在若干个数（都是 g 的倍数），它们的最大公约数恰好是 g
// 则 g 是一个合法的子序列 GCD
// 时间复杂度: O(max_num * log(max_num)), 空间复杂度: O(max_num)
static int solution(vector<int>& nums) {
  if (nums.empty()) return 0;

  int max_num = *max_element(nums.begin(), nums.end());

  // 标记哪些数字在数组中出现过
  vector<bool> exists(max_num + 1, false);
  for (int num : nums) {
    exists[num] = true;
  }

  int result = 0;

  // 枚举每个可能的 GCD 值 g
  for (int g = 1; g <= max_num; ++g) {
    int current_gcd = 0;  // 0 表示还没有找到任何倍数

    // 枚举 g 的所有倍数
    for (int multiple = g; multiple <= max_num; multiple += g) {
      if (exists[multiple]) {
        if (current_gcd == 0) {
          current_gcd = multiple;
        } else {
          current_gcd = std::gcd(current_gcd, multiple);
        }
        // 如果当前 GCD 已经等于 g，可以提前退出（不可能更小）
        if (current_gcd == g) {
          break;
        }
      }
    }

    // 如果所有 g 的倍数的最大公约数恰好是 g，则 g 是一个合法的 GCD
    if (current_gcd == g) {
      ++result;
    }
  }

  return result;
}

NumberOfDifferentSubsequencesGcdsSolution::NumberOfDifferentSubsequencesGcdsSolution() {
  setMetaInfo({.id = 1819,
               .title = "Number of Different Subsequences GCDs",
               .url = "https://leetcode.com/problems/number-of-different-subsequences-gcds/"});
  registerStrategy("Enumerate GCD", solution);
}

int NumberOfDifferentSubsequencesGcdsSolution::countDifferentSubsequenceGCDs(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1819
}  // namespace leetcode
