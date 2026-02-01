
#include "leetcode/problems/minimize-the-maximum-difference-of-pairs.h"

namespace leetcode {
namespace problem_2616 {

// 二分查找 + 贪心
// 思路：
// 1. 对数组排序，这样相邻元素差值较小，易于配对
// 2. 二分查找最小的最大差值
// 3. 对于候选值 mid，使用贪心检查是否能形成至少 p 对，每对差值 ≤ mid
//    - 排序后遍历，如果当前元素与下一个元素差值 ≤ mid，则配对成功，跳过这两个元素
//    - 否则跳过当前元素
// 时间复杂度: O(n log n + n log(max_diff)), 空间复杂度: O(1)
static int solution1(vector<int>& nums, int p) {
  if (p == 0) return 0;
  
  const int n = nums.size();
  sort(nums.begin(), nums.end());
  
  // 二分查找范围：[0, nums[n-1] - nums[0]]
  int left = 0;
  int right = nums[n - 1] - nums[0];
  int answer = right;
  
  while (left <= right) {
    int mid = left + (right - left) / 2;
    
    // 贪心检查：能否形成至少 p 对，每对差值 ≤ mid
    int count = 0;
    for (int i = 0; i < n - 1; ++i) {
      if (nums[i + 1] - nums[i] <= mid) {
        // 找到一对，跳过这两个元素
        ++count;
        ++i;  // 跳过下一个元素，因为已经配对
      }
      if (count >= p) break;
    }
    
    if (count >= p) {
      // 可以形成 p 对，尝试更小的最大差值
      answer = mid;
      right = mid - 1;
    } else {
      // 无法形成 p 对，需要增大最大差值
      left = mid + 1;
    }
  }
  
  return answer;
}

MinimizeTheMaximumDifferenceOfPairsSolution::MinimizeTheMaximumDifferenceOfPairsSolution() {
  setMetaInfo({.id = 2616,
               .title = "Minimize the Maximum Difference of Pairs",
               .url = "https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/"});
  registerStrategy("Binary Search + Greedy", solution1);
}

int MinimizeTheMaximumDifferenceOfPairsSolution::minimizeMax(vector<int>& nums, int p) {
  return getSolution()(nums, p);
}

}  // namespace problem_2616
}  // namespace leetcode
