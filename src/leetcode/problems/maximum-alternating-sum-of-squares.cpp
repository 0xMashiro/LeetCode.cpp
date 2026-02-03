#include "leetcode/problems/maximum-alternating-sum-of-squares.h"

namespace leetcode {
namespace problem_3727 {

// 贪心策略：
// 1. 将数组按绝对值从大到小排序
// 2. 前 ceil(n/2) 个较大的数放在正位置（加）
// 3. 后 floor(n/2) 个较小的数放在负位置（减）
// 时间复杂度: O(n log n), 空间复杂度: O(1)
static long long solution1(vector<int>& nums) {
  // 按绝对值从大到小排序
  sort(nums.begin(), nums.end(), [](int a, int b) {
    return abs(a) > abs(b);
  });
  
  int n = nums.size();
  int positiveCount = (n + 1) / 2;  // 正位置个数（偶数索引）
  int negativeCount = n / 2;         // 负位置个数（奇数索引）
  
  long long result = 0;
  
  // 前 positiveCount 个数放在正位置（加）
  for (int i = 0; i < positiveCount; ++i) {
    result += 1LL * nums[i] * nums[i];
  }
  
  // 后 negativeCount 个数放在负位置（减）
  for (int i = positiveCount; i < n; ++i) {
    result -= 1LL * nums[i] * nums[i];
  }
  
  return result;
}

MaximumAlternatingSumOfSquaresSolution::MaximumAlternatingSumOfSquaresSolution() {
  setMetaInfo({.id = 3727,
               .title = "Maximum Alternating Sum of Squares",
               .url = "https://leetcode.com/problems/maximum-alternating-sum-of-squares/"});
  registerStrategy("Greedy Sort", solution1);
}

long long MaximumAlternatingSumOfSquaresSolution::maxAlternatingSum(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3727
}  // namespace leetcode
