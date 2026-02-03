
#include "leetcode/problems/count-the-number-of-fair-pairs.h"

namespace leetcode {
namespace problem_2563 {

// 排序 + 双指针
// 时间复杂度: O(n log n), 空间复杂度: O(1) 或 O(n)（取决于排序实现）
// 核心思路：先排序，对于每个 nums[i]，找到满足 lower <= nums[i] + nums[j] <= upper 的 j 的范围
// 即：lower - nums[i] <= nums[j] <= upper - nums[i]
// 由于 i < j，我们只需要在 i 之后的范围内查找
static long long solution1(vector<int>& nums, int lower, int upper) {
  const int n = nums.size();
  sort(nums.begin(), nums.end());
  
  long long count = 0;
  
  // 对于每个 i，找满足条件的 j 的数量，其中 j > i
  for (int i = 0; i < n; ++i) {
    // 需要找 nums[j] 满足：lower - nums[i] <= nums[j] <= upper - nums[i]
    // 且 j > i，所以在 [i+1, n-1] 范围内查找
    
    long long low_val = (long long)lower - nums[i];
    long long high_val = (long long)upper - nums[i];
    
    // 找第一个 >= low_val 的位置（左边界）
    auto left_it = lower_bound(nums.begin() + i + 1, nums.end(), low_val);
    // 找第一个 > high_val 的位置，即最后一个 <= high_val 的位置 + 1（右边界）
    auto right_it = upper_bound(nums.begin() + i + 1, nums.end(), high_val);
    
    // 范围内的元素个数就是满足条件的 j 的数量
    count += (right_it - left_it);
  }
  
  return count;
}

// 另一种双指针写法：先统计 <= upper 的数对，再统计 <= lower-1 的数对，相减
// 时间复杂度: O(n log n), 空间复杂度: O(1)
static long long solution2(vector<int>& nums, int lower, int upper) {
  const int n = nums.size();
  sort(nums.begin(), nums.end());
  
  auto countLessEqual = [&](int target) -> long long {
    long long count = 0;
    int left = 0, right = n - 1;
    while (left < right) {
      long long sum = (long long)nums[left] + nums[right];
      if (sum <= target) {
        // 如果 nums[left] + nums[right] <= target
        // 那么对于当前 left，所有 [left+1, right] 范围内的 j 都满足条件
        count += (right - left);
        ++left;
      } else {
        --right;
      }
    }
    return count;
  };
  
  // 答案 = (和 <= upper 的数对数) - (和 <= lower-1 的数对数)
  return countLessEqual(upper) - countLessEqual(lower - 1);
}

CountTheNumberOfFairPairsSolution::CountTheNumberOfFairPairsSolution() {
  setMetaInfo({.id = 2563,
               .title = "Count the Number of Fair Pairs",
               .url = "https://leetcode.com/problems/count-the-number-of-fair-pairs/"});
  registerStrategy("Sorting + Binary Search", solution1);
  registerStrategy("Sorting + Two Pointer", solution2);
}

long long CountTheNumberOfFairPairsSolution::countFairPairs(vector<int>& nums, int lower, int upper) {
  return getSolution()(nums, lower, upper);
}

}  // namespace problem_2563
}  // namespace leetcode
