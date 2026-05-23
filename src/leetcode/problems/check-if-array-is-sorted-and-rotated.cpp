#include "leetcode/problems/check-if-array-is-sorted-and-rotated.h"

namespace leetcode {
namespace problem_1752 {

// 解法1：暴力模拟旋转
// 尝试每个位置作为旋转起点，检查从该点开始的序列是否非递减
// 时间复杂度: O(n^2), 空间复杂度: O(1)
static bool solution1(vector<int>& nums) {
  const int n = nums.size();
  // 枚举旋转起点（从 0 到 n-1）
  for (int start = 0; start < n; ++start) {
    bool sorted = true;
    for (int i = 0; i < n - 1; ++i) {
      int cur = nums[(start + i) % n];
      int nxt = nums[(start + i + 1) % n];
      if (cur > nxt) {
        sorted = false;
        break;
      }
    }
    if (sorted) return true;
  }
  return false;
}

// 解法2：统计断点法（最优）
// 非递减排序数组旋转后，最多只有 1 个位置 nums[i] > nums[i+1]
// 我们统计这样的下降次数，如果 ≤ 1 则为 true
// 时间复杂度: O(n), 空间复杂度: O(1)
static bool solution2(vector<int>& nums) {
  const int n = nums.size();
  int dropCount = 0;
  for (int i = 0; i < n; ++i) {
    if (nums[i] > nums[(i + 1) % n]) {
      ++dropCount;
      if (dropCount > 1) return false;
    }
  }
  return true;
}

CheckIfArrayIsSortedAndRotatedSolution::CheckIfArrayIsSortedAndRotatedSolution() {
  setMetaInfo({.id = 1752,
               .title = "Check if Array Is Sorted and Rotated",
               .url = "https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/"});
  registerStrategy("Brute Force", solution1);
  registerStrategy("Count Drops", solution2);
}

bool CheckIfArrayIsSortedAndRotatedSolution::check(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1752
}  // namespace leetcode
