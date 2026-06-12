#include "leetcode/problems/maximum-total-subarray-value-i.h"

namespace leetcode {
namespace problem_3689 {

// 本题结构唯一合理解为 O(n) 线性扫描找全局 max 和 min
// 每个子数组 value = max - min <= 全局 max - 全局 min
// 整个数组 [0..n-1] 同时包含全局 max 和 min，value 达到上界
// 最优策略：选整个数组 k 次，答案 = k * (全局 max - 全局 min)
// 时间复杂度: O(n), 空间复杂度: O(1)
static long long solution1(vector<int>& nums, int k) {
  if (nums.empty()) return 0;
  int maxVal = nums[0], minVal = nums[0];
  for (int num : nums) {
    if (num > maxVal) maxVal = num;
    if (num < minVal) minVal = num;
  }
  return (long long)k * (maxVal - minVal);
}

MaximumTotalSubarrayValueISolution::MaximumTotalSubarrayValueISolution() {
  setMetaInfo({.id = 3689,
               .title = "Maximum Total Subarray Value I",
               .url = "https://leetcode.com/problems/maximum-total-subarray-value-i/"});
  registerStrategy({.name = "Greedy (Global Max - Min)"}, solution1);
}

long long MaximumTotalSubarrayValueISolution::maxTotalValue(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3689
}  // namespace leetcode
