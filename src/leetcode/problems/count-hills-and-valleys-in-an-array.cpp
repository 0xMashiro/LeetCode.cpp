#include "leetcode/problems/count-hills-and-valleys-in-an-array.h"

namespace leetcode {
namespace problem_2210 {

// 压缩数组 + 直接判断
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  if (n < 3) return 0;

  // 压缩数组：去除连续重复元素
  vector<int> compressed;
  compressed.push_back(nums[0]);
  for (int i = 1; i < n; ++i) {
    if (nums[i] != nums[i - 1]) {
      compressed.push_back(nums[i]);
    }
  }

  int count = 0;
  const int m = compressed.size();
  // 检查每个中间元素
  for (int i = 1; i < m - 1; ++i) {
    if (compressed[i] > compressed[i - 1] && compressed[i] > compressed[i + 1]) {
      // 山峰
      ++count;
    } else if (compressed[i] < compressed[i - 1] && compressed[i] < compressed[i + 1]) {
      // 山谷
      ++count;
    }
  }

  return count;
}

// 原地计算：不需要额外空间
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution2(vector<int>& nums) {
  const int n = nums.size();
  if (n < 3) return 0;

  int count = 0;
  int left = 0;  // 左边最近的不相等元素位置

  for (int i = 1; i < n - 1; ++i) {
    if (nums[i] == nums[i + 1]) continue;  // 跳过相等的，它们属于同一组

    // 现在 nums[i] != nums[i+1]，检查是否为山峰或山谷
    if (nums[i] > nums[left] && nums[i] > nums[i + 1]) {
      ++count;  // 山峰
    } else if (nums[i] < nums[left] && nums[i] < nums[i + 1]) {
      ++count;  // 山谷
    }

    left = i;  // 更新左边最近的不相等位置
  }

  return count;
}

CountHillsAndValleysInAnArraySolution::CountHillsAndValleysInAnArraySolution() {
  setMetaInfo({
    .id = 2210,
    .title = "Count Hills and Valleys in an Array",
    .url = "https://leetcode.com/problems/count-hills-and-valleys-in-an-array/"
  });
  registerStrategy("Compressed Array", solution1);
  registerStrategy("In-place", solution2);
}

int CountHillsAndValleysInAnArraySolution::countHillValley(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2210
}  // namespace leetcode
