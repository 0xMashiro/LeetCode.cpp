#include "leetcode/problems/trapping-rain-water.h"

namespace leetcode {
namespace problem_42 {

/**
 * 双指针法求解接雨水问题
 * 
 * 思路：
 * 1. 使用两个指针 l 和 r 分别从数组两端向中间移动
 * 2. 维护 left_max 和 right_max 记录左右两边遇到的最大高度
 * 3. 如果 height[l] < height[r]，说明左边是瓶颈：
 *    - 如果 height[l] >= left_max，更新 left_max
 *    - 否则，left_max - height[l] 就是当前位置能接的雨水量
 *    - 左指针右移
 * 4. 否则，右边是瓶颈，同理处理右边
 * 
 * 为什么移动较矮的一边？
 * 因为接水量取决于两边最大值的较小值。当 height[l] < height[r] 时，
 * left_max 一定 <= right_max（因为 left_max <= height[l] < height[r] <= right_max），
 * 所以 left_max 是瓶颈，可以计算左边位置的接水量。
 */
static int solution1(vector<int>& height) {
  const int n = height.size();
  if (n <= 2) return 0;  // 至少需要3个柱子才能积水
  
  int l = 0, r = n - 1;
  int left_max = 0, right_max = 0;
  int water = 0;
  
  while (l < r) {
    if (height[l] < height[r]) {
      // 左边是瓶颈
      if (height[l] >= left_max) {
        left_max = height[l];
      } else {
        water += left_max - height[l];
      }
      ++l;
    } else {
      // 右边是瓶颈
      if (height[r] >= right_max) {
        right_max = height[r];
      } else {
        water += right_max - height[r];
      }
      --r;
    }
  }
  
  return water;
}

/**
 * 动态规划法（备用方案）
 * 
 * 思路：
 * 1. 预处理 left_max[i]：表示位置 i 左边（包括 i）的最大高度
 * 2. 预处理 right_max[i]：表示位置 i 右边（包括 i）的最大高度
 * 3. 对于每个位置 i，接水量 = min(left_max[i], right_max[i]) - height[i]
 * 
 * 时间复杂度: O(n), 空间复杂度: O(n)
 */
static int solution2(vector<int>& height) {
  const int n = height.size();
  if (n <= 2) return 0;
  
  vector<int> left_max(n), right_max(n);
  
  // 预处理左边最大高度
  left_max[0] = height[0];
  for (int i = 1; i < n; ++i) {
    left_max[i] = max(left_max[i - 1], height[i]);
  }
  
  // 预处理右边最大高度
  right_max[n - 1] = height[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    right_max[i] = max(right_max[i + 1], height[i]);
  }
  
  // 计算接水量
  int water = 0;
  for (int i = 0; i < n; ++i) {
    water += min(left_max[i], right_max[i]) - height[i];
  }
  
  return water;
}

TrappingRainWaterSolution::TrappingRainWaterSolution() {
  setMetaInfo({.id = 42,
               .title = "Trapping Rain Water",
               .url = "https://leetcode.com/problems/trapping-rain-water/"});
  registerStrategy("Two Pointers", solution1);
  registerStrategy("Dynamic Programming", solution2);
}

int TrappingRainWaterSolution::trap(vector<int>& height) {
  return getSolution()(height);
}

}  // namespace problem_42
}  // namespace leetcode
