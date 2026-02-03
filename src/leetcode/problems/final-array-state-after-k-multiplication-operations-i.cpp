
#include "leetcode/problems/final-array-state-after-k-multiplication-operations-i.h"

namespace leetcode {
namespace problem_3264 {

// 暴力模拟：每次找到最小值，乘以 multiplier
// 时间复杂度: O(k * n), 空间复杂度: O(1)
static vector<int> solution1(vector<int>& nums, int k, int multiplier) {
  int n = nums.size();
  for (int op = 0; op < k; ++op) {
    // 找到最小值的索引（第一个出现的最小值）
    int minIdx = 0;
    for (int i = 1; i < n; ++i) {
      if (nums[i] < nums[minIdx]) {
        minIdx = i;
      }
    }
    // 乘以 multiplier
    nums[minIdx] *= multiplier;
  }
  return nums;
}

FinalArrayStateAfterKMultiplicationOperationsISolution::FinalArrayStateAfterKMultiplicationOperationsISolution() {
  setMetaInfo({.id = 3264,
               .title = "Final Array State After K Multiplication Operations I",
               .url = "https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/"});
  registerStrategy("Brute Force", solution1);
}

vector<int> FinalArrayStateAfterKMultiplicationOperationsISolution::getFinalState(vector<int>& nums, int k, int multiplier) {
  return getSolution()(nums, k, multiplier);
}

}  // namespace problem_3264
}  // namespace leetcode
