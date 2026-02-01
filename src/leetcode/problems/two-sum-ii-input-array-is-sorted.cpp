
#include "leetcode/problems/two-sum-ii-input-array-is-sorted.h"

namespace leetcode {
namespace problem_167 {

/**
 * 双指针解法
 * 左指针从数组开头开始，右指针从数组末尾开始
 * - 如果两数之和等于 target，返回索引（+1）
 * - 如果和小于 target，左指针右移（需要更大的数）
 * - 如果和大于 target，右指针左移（需要更小的数）
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(1)
 */
static vector<int> solution1(vector<int>& numbers, int target) {
  int left = 0;
  int right = numbers.size() - 1;

  while (left < right) {
    int sum = numbers[left] + numbers[right];
    if (sum == target) {
      // 返回 1-indexed 的索引
      return {left + 1, right + 1};
    } else if (sum < target) {
      // 和太小，左指针右移以增大和
      ++left;
    } else {
      // 和太大，右指针左移以减小和
      --right;
    }
  }

  // 根据题目保证，不会执行到这里
  return {};
}

/**
 * 二分查找解法（替代方案）
 * 对于每个元素，用二分查找找其补数
 *
 * 时间复杂度: O(n log n)
 * 空间复杂度: O(1)
 */
static vector<int> solution2(vector<int>& numbers, int target) {
  const int n = numbers.size();

  for (int i = 0; i < n; ++i) {
    int complement = target - numbers[i];
    // 在 [i+1, n-1] 范围内二分查找 complement
    int lo = i + 1, hi = n - 1;
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      if (numbers[mid] == complement) {
        return {i + 1, mid + 1};
      } else if (numbers[mid] < complement) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }
  }

  return {};
}

TwoSumIiInputArrayIsSortedSolution::TwoSumIiInputArrayIsSortedSolution() {
  setMetaInfo({.id = 167,
               .title = "Two Sum II - Input Array Is Sorted",
               .url = "https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/"});
  registerStrategy("Two Pointers", solution1);
  registerStrategy("Binary Search", solution2);
}

vector<int> TwoSumIiInputArrayIsSortedSolution::twoSum(vector<int>& numbers, int target) {
  return getSolution()(numbers, target);
}

}  // namespace problem_167
}  // namespace leetcode
