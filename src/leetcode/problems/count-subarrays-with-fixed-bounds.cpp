#include "leetcode/problems/count-subarrays-with-fixed-bounds.h"

namespace leetcode {
namespace problem_2444 {

// 本题结构唯一合理解为 O(n) 线性扫描，无明显多解
//
// 核心思想：
//   遍历数组，维护三个关键位置：
//   - last_bad: 最后一个不在 [minK, maxK] 范围内的元素位置
//   - last_min: 最后一个等于 minK 的元素位置
//   - last_max: 最后一个等于 maxK 的元素位置
//
//   以位置 i 为右端点的合法子数组需要同时满足：
//   1. 子数组中所有元素都在 [minK, maxK] 内 => 左端点 > last_bad
//   2. 子数组中同时包含 minK 和 maxK => 左端点 <= min(last_min, last_max)
//
//   因此左端点取值范围为 (last_bad, min(last_min, last_max)]
//   对当前 i 的贡献 = max(0, min(last_min, last_max) - last_bad)
//
// 时间复杂度: O(n), 空间复杂度: O(1)
static long long solution1(vector<int>& nums, int minK, int maxK) {
  long long ans = 0;
  int last_bad = -1;
  int last_min = -1;
  int last_max = -1;
  const int n = nums.size();

  for (int i = 0; i < n; ++i) {
    // 非法元素：不在 [minK, maxK] 范围内
    if (nums[i] < minK || nums[i] > maxK) {
      last_bad = i;
    }
    if (nums[i] == minK) {
      last_min = i;
    }
    if (nums[i] == maxK) {
      last_max = i;
    }

    int left_boundary = min(last_min, last_max);
    if (left_boundary > last_bad) {
      ans += left_boundary - last_bad;
    }
  }

  return ans;
}

CountSubarraysWithFixedBoundsSolution::CountSubarraysWithFixedBoundsSolution() {
  setMetaInfo({.id = 2444,
               .title = "Count Subarrays With Fixed Bounds",
               .url = "https://leetcode.com/problems/count-subarrays-with-fixed-bounds/"});
  registerStrategy({.name = "Linear Scan"}, solution1);
}

long long CountSubarraysWithFixedBoundsSolution::countSubarrays(vector<int>& nums, int minK, int maxK) {
  return getSolution()(nums, minK, maxK);
}

}  // namespace problem_2444
}  // namespace leetcode
