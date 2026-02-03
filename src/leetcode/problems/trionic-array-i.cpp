#include "leetcode/problems/trionic-array-i.h"

namespace leetcode {
namespace problem_3637 {

// 暴力枚举：遍历所有可能的 p 和 q 组合
// 时间复杂度: O(n^3), 空间复杂度: O(1)
// 由于 n <= 100，O(n^3) = 1e6，完全可以接受
static bool solution1(vector<int>& nums) {
  const int n = nums.size();
  
  // p 的范围：1 到 n-3（因为 q 至少要是 p+1，且 q <= n-2）
  for (int p = 1; p <= n - 3; ++p) {
    // q 的范围：p+1 到 n-2
    for (int q = p + 1; q <= n - 2; ++q) {
      bool valid = true;
      
      // 检查第一段：nums[0...p] 严格递增
      for (int i = 0; i < p && valid; ++i) {
        if (nums[i] >= nums[i + 1]) {
          valid = false;
        }
      }
      
      // 检查第二段：nums[p...q] 严格递减
      for (int i = p; i < q && valid; ++i) {
        if (nums[i] <= nums[i + 1]) {
          valid = false;
        }
      }
      
      // 检查第三段：nums[q...n-1] 严格递增
      for (int i = q; i < n - 1 && valid; ++i) {
        if (nums[i] >= nums[i + 1]) {
          valid = false;
        }
      }
      
      if (valid) {
        return true;
      }
    }
  }
  
  return false;
}

// 优化版本：一次遍历确定 p 和 q
// 时间复杂度: O(n), 空间复杂度: O(1)
static bool solution2(vector<int>& nums) {
  const int n = nums.size();
  int i = 0;
  
  // 找到第一段递增的结束位置（峰值）
  while (i < n - 1 && nums[i] < nums[i + 1]) {
    ++i;
  }
  
  // 第一段必须至少有两个元素，且后面还有元素用于递减和递增
  // i 是峰值位置，即 p
  if (i == 0 || i >= n - 2) {
    return false;
  }
  
  int p = i;
  
  // 找到第二段递减的结束位置（谷值）
  while (i < n - 1 && nums[i] > nums[i + 1]) {
    ++i;
  }
  
  // 第二段必须至少有一个元素
  if (i == p) {
    return false;
  }
  
  int q = i;
  
  // 第三段必须严格递增到数组末尾
  while (i < n - 1 && nums[i] < nums[i + 1]) {
    ++i;
  }
  
  // 检查是否到达数组末尾，且第三段至少有两个元素
  // q 必须 <= n-2 才能保证第三段至少有两个元素
  return i == n - 1 && q <= n - 2;
}

TrionicArrayISolution::TrionicArrayISolution() {
  setMetaInfo({.id = 3637,
               .title = "Trionic Array I",
               .url = "https://leetcode.com/problems/trionic-array-i/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("One Pass", solution2);
}

bool TrionicArrayISolution::isTrionic(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3637
}  // namespace leetcode