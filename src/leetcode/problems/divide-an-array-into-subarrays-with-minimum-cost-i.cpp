#include "leetcode/problems/divide-an-array-into-subarrays-with-minimum-cost-i.h"

namespace leetcode {
namespace problem_3010 {

// 思路：第一个子数组必须从nums[0]开始，代价固定为nums[0]
// 需要在nums[1..n-1]中选择两个位置作为第二、三个子数组的起点
// 目标是最小化这两个起点的值之和
// 因此只需找出nums[1..n-1]中最小的两个数
// 时间复杂度: O(n), 空间复杂度: O(1)
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  // 第一个子数组的代价固定
  int first = nums[0];
  
  // 在nums[1..n-1]中找两个最小值
  int min1 = INT_MAX;  // 最小值
  int min2 = INT_MAX;  // 次小值
  
  for (int i = 1; i < n; ++i) {
    if (nums[i] < min1) {
      min2 = min1;
      min1 = nums[i];
    } else if (nums[i] < min2) {
      min2 = nums[i];
    }
  }
  
  return first + min1 + min2;
}

// 备选方案：使用排序
// 时间复杂度: O(n log n), 空间复杂度: O(1)或O(n)
static int solution2(vector<int>& nums) {
  const int n = nums.size();
  int first = nums[0];
  
  // 复制nums[1..n-1]并排序
  vector<int> rest(nums.begin() + 1, nums.end());
  sort(rest.begin(), rest.end());
  
  return first + rest[0] + rest[1];
}

DivideAnArrayIntoSubarraysWithMinimumCostISolution::DivideAnArrayIntoSubarraysWithMinimumCostISolution() {
  setMetaInfo({.id = 3010,
               .title = "Divide an Array Into Subarrays With Minimum Cost I",
               .url = "https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-i/"});
  registerStrategy("Two Minimum Linear", solution1);
  registerStrategy("Sorting", solution2);
}

int DivideAnArrayIntoSubarraysWithMinimumCostISolution::minimumCost(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3010
}  // namespace leetcode
