
#include "leetcode/problems/find-k-th-smallest-pair-distance.h"

namespace leetcode {
namespace problem_719 {

/**
 * 使用二分查找 + 双指针求解
 * 
 * 核心思想：
 * 1. 排序数组，方便后续处理
 * 2. 二分查找可能的距离值（0 到 max-min）
 * 3. 对于每个候选距离 mid，用双指针统计有多少对数字的距离 ≤ mid
 * 4. 根据统计结果调整二分查找范围
 * 
 * 时间复杂度: O(n log n + n log(max-min))
 *   - 排序: O(n log n)
 *   - 二分查找: O(log(max-min)) 次迭代
 *   - 每次迭代的计数: O(n) 双指针
 * 空间复杂度: O(1)
 */
static int solution(vector<int>& nums, int k) {
  const int n = nums.size();
  
  // 1. 排序
  sort(nums.begin(), nums.end());
  
  // 2. 二分查找范围：[0, max - min]
  int left = 0;
  int right = nums[n - 1] - nums[0];
  
  auto countPairsWithDistanceAtMost = [&](int maxDist) -> int {
    int count = 0;
    int j = 0;
    // 双指针：对于每个 nums[i]，找到最大的 j 使得 nums[j] - nums[i] <= maxDist
    for (int i = 0; i < n; ++i) {
      // 移动 j 直到 nums[j] - nums[i] > maxDist
      while (j < n && nums[j] - nums[i] <= maxDist) {
        ++j;
      }
      // nums[i+1..j-1] 与 nums[i] 的距离都 <= maxDist
      // 对数 = (j - 1) - (i + 1) + 1 = j - i - 1
      count += j - i - 1;
    }
    return count;
  };
  
  // 3. 二分查找第 k 小的距离
  while (left < right) {
    int mid = left + (right - left) / 2;
    int count = countPairsWithDistanceAtMost(mid);
    
    if (count < k) {
      // 距离 <= mid 的对数不足 k，说明第 k 小的距离 > mid
      left = mid + 1;
    } else {
      // 距离 <= mid 的对数 >= k，说明第 k 小的距离 <= mid
      right = mid;
    }
  }
  
  return left;
}

FindKThSmallestPairDistanceSolution::FindKThSmallestPairDistanceSolution() {
  setMetaInfo({.id = 719,
               .title = "Find K-th Smallest Pair Distance",
               .url = "https://leetcode.com/problems/find-k-th-smallest-pair-distance/"});
  registerStrategy("Binary Search + Two Pointers", solution);
}

int FindKThSmallestPairDistanceSolution::smallestDistancePair(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_719
}  // namespace leetcode
