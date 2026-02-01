#include "leetcode/problems/adjacent-increasing-subarrays-detection-ii.h"

namespace leetcode {
namespace problem_3350 {

// 最优解法：预处理 + 二分查找
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static int solution(vector<int>& nums) {
  int n = nums.size();
  if (n < 2) return 0;
  
  // inc[i]: 以位置 i 结尾的最长严格递增子数组的长度
  vector<int> inc(n, 1);
  for (int i = 1; i < n; ++i) {
    if (nums[i] > nums[i - 1]) {
      inc[i] = inc[i - 1] + 1;
    }
  }
  
  // start[i]: 从位置 i 开始的最长严格递增子数组的长度
  vector<int> start(n, 1);
  for (int i = n - 2; i >= 0; --i) {
    if (nums[i] < nums[i + 1]) {
      start[i] = start[i + 1] + 1;
    }
  }
  
  // 辅助函数：检查是否存在两个相邻的长度为 k 的严格递增子数组
  auto check = [&](int k) -> bool {
    // 第一个子数组以 i 结尾，第二个从 i+1 开始
    // 需要 inc[i] >= k 且 start[i+1] >= k
    for (int i = k - 1; i < n - k; ++i) {
      if (inc[i] >= k && start[i + 1] >= k) {
        return true;
      }
    }
    return false;
  };
  
  // 二分查找最大的 k
  int left = 1, right = n / 2, ans = 0;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (check(mid)) {
      ans = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  
  return ans;
}

AdjacentIncreasingSubarraysDetectionIiSolution::AdjacentIncreasingSubarraysDetectionIiSolution() {
  setMetaInfo({.id = 3350,
               .title = "Adjacent Increasing Subarrays Detection II",
               .url = "https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/"});
  registerStrategy("Binary Search + DP", solution);
}

int AdjacentIncreasingSubarraysDetectionIiSolution::maxIncreasingSubarrays(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3350
}  // namespace leetcode
