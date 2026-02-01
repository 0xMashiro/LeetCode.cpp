
#include "leetcode/problems/absolute-difference-between-maximum-and-minimum-k-elements.h"

namespace leetcode {
namespace problem_3774 {

// 排序解法
// 对数组排序，前k个是最小元素，后k个是最大元素
// 时间复杂度: O(n log n), 空间复杂度: O(1) (或 O(n) 取决于排序实现)
static int solution1(vector<int>& nums, int k) {
  sort(nums.begin(), nums.end());
  
  long long minSum = 0;  // 使用 long long 防止溢出
  long long maxSum = 0;
  
  // k个最小元素的和（排序后的前k个）
  for (int i = 0; i < k; ++i) {
    minSum += nums[i];
  }
  
  // k个最大元素的和（排序后的后k个）
  int n = nums.size();
  for (int i = n - k; i < n; ++i) {
    maxSum += nums[i];
  }
  
  return static_cast<int>(abs(maxSum - minSum));
}

AbsoluteDifferenceBetweenMaximumAndMinimumKElementsSolution::AbsoluteDifferenceBetweenMaximumAndMinimumKElementsSolution() {
  setMetaInfo({.id = 3774,
               .title = "Absolute Difference Between Maximum and Minimum K Elements",
               .url = "https://leetcode.com/problems/absolute-difference-between-maximum-and-minimum-k-elements/"});
  registerStrategy("Sorting", solution1);
}

int AbsoluteDifferenceBetweenMaximumAndMinimumKElementsSolution::absDifference(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3774
}  // namespace leetcode
