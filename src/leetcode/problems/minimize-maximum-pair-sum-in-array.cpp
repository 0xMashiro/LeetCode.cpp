
#include "leetcode/problems/minimize-maximum-pair-sum-in-array.h"

namespace leetcode {
namespace problem_1877 {

// Strategy 1: Sorting + Two Pointers
// Time complexity: O(n log n), Space complexity: O(log n) for sorting
static int solution1(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  int left = 0, right = nums.size() - 1;
  int max_pair_sum = 0;
  while (left < right) {
    max_pair_sum = max(max_pair_sum, nums[left] + nums[right]);
    ++left;
    --right;
  }
  return max_pair_sum;
}

// Strategy 2: Counting Sort + Two Pointers
// Time complexity: O(n + M) where M = 100001, Space complexity: O(M)
static int solution2(vector<int>& nums) {
  const int kMaxValue = 100001;
  vector<int> count(kMaxValue, 0);
  
  for (int num : nums) {
    ++count[num];
  }
  
  int left = 1, right = kMaxValue - 1;
  int max_pair_sum = 0;
  
  while (left <= right) {
    // Skip empty buckets
    while (left <= right && count[left] == 0) ++left;
    while (left <= right && count[right] == 0) --right;
    
    if (left > right) break;
    
    // Pair the smallest with the largest
    max_pair_sum = max(max_pair_sum, left + right);
    
    // Consume one pair (two elements)
    --count[left];
    --count[right];
    
    // When left == right, we consumed two elements from the same bucket
    // The above two decrements already handled this case (same bucket)
  }
  
  return max_pair_sum;
}

MinimizeMaximumPairSumInArraySolution::MinimizeMaximumPairSumInArraySolution() {
  setMetaInfo({.id = 1877,
               .title = "Minimize Maximum Pair Sum in Array",
               .url = "https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/"});
  registerStrategy({.name = "Sorting + Two Pointers"}, solution1);
  registerStrategy({.name = "Counting Sort + Two Pointers"}, solution2);
}

int MinimizeMaximumPairSumInArraySolution::minPairSum(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_1877
}  // namespace leetcode