#include "leetcode/problems/minimum-removals-to-balance-array.h"

namespace leetcode {
namespace problem_3634 {

// 双指针（滑动窗口）解法
// 1. 先排序数组
// 2. 对于每个左端点 i，找到最大的右端点 j 使得 nums[j] <= nums[i] * k
// 3. 窗口长度 j - i + 1 就是以 nums[i] 为最小值的平衡子数组的最大长度
// 4. 答案 = n - 最大窗口长度
// 时间复杂度: O(n log n) 主要是排序
// 空间复杂度: O(1) 或 O(n) 取决于排序实现
static int solution1(vector<int>& nums, int k) {
  const int n = nums.size();
  if (n <= 1) return 0;
  
  sort(nums.begin(), nums.end());
  
  int maxLen = 1;  // 至少可以保留一个元素
  int j = 0;
  
  for (int i = 0; i < n; ++i) {
    // 对于当前 i，找到最大的 j 使得 nums[j] <= nums[i] * k
    // 由于数组有序，可以用双指针维护
    while (j < n && static_cast<long long>(nums[j]) <= static_cast<long long>(nums[i]) * k) {
      ++j;
    }
    // 窗口为 [i, j-1]，长度为 j - i
    maxLen = max(maxLen, j - i);
  }
  
  return n - maxLen;
}

// 优化版本：更简洁的双指针
static int solution2(vector<int>& nums, int k) {
  const int n = nums.size();
  sort(nums.begin(), nums.end());
  
  int maxLen = 0;
  int j = 0;
  
  for (int i = 0; i < n; ++i) {
    long long limit = static_cast<long long>(nums[i]) * k;
    while (j < n && nums[j] <= limit) {
      ++j;
    }
    maxLen = max(maxLen, j - i);
  }
  
  return n - maxLen;
}

MinimumRemovalsToBalanceArraySolution::MinimumRemovalsToBalanceArraySolution() {
  setMetaInfo({
    .id = 3634,
    .title = "Minimum Removals to Balance Array",
    .url = "https://leetcode.com/problems/minimum-removals-to-balance-array/"
  });
  registerStrategy("Two Pointer", solution1);
  registerStrategy("Two Pointer Optimized", solution2);
}

int MinimumRemovalsToBalanceArraySolution::minRemoval(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3634
}  // namespace leetcode