#include "leetcode/problems/maximum-subarray-sum-with-length-divisible-by-k.h"

namespace leetcode {
namespace problem_3381 {

// 前缀和 + 分组最小值
// 对于子数组 nums[i..j-1]，长度 L = j-i 需要被 k 整除
// 子数组和 = prefix[j] - prefix[i]，其中 prefix[x] 是前 x 个元素的和
// 要求 j-i ≡ 0 (mod k)，即 j ≡ i (mod k)
// 所以对于位置 j，需要在同余数组 (i % k = j % k) 中找到最小的 prefix[i]
// 时间复杂度: O(n), 空间复杂度: O(k)
static long long solution1(vector<int>& nums, int k) {
  const int n = nums.size();
  
  // min_prefix[r] 表示在余数为 r 的组中，之前出现过的最小前缀和
  // 初始化为无穷大
  vector<long long> min_prefix(k, LLONG_MAX);
  
  long long prefix = 0;  // 当前前缀和
  long long ans = LLONG_MIN;  // 答案初始化为负无穷
  
  for (int i = 0; i <= n; ++i) {
    int r = i % k;  // 当前位置的余数
    
    if (i >= k) {
      // 只有当 i >= k 时，才能形成长度至少为 k 的子数组
      // 此时可以计算以位置 i 结尾、长度能被 k 整除的子数组的最大和
      if (min_prefix[r] != LLONG_MAX) {
        ans = max(ans, prefix - min_prefix[r]);
      }
    }
    
    // 更新当前余数组的最小前缀和
    // 注意：这里要先计算答案再更新，因为子数组长度至少为 k
    // 所以当前 prefix 应该留给后面的位置使用
    min_prefix[r] = min(min_prefix[r], prefix);
    
    // 累加下一个元素（如果还有）
    if (i < n) {
      prefix += nums[i];
    }
  }
  
  return ans;
}

MaximumSubarraySumWithLengthDivisibleByKSolution::MaximumSubarraySumWithLengthDivisibleByKSolution() {
  setMetaInfo({.id = 3381,
               .title = "Maximum Subarray Sum With Length Divisible by K",
               .url = "https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/"});
  registerStrategy("Prefix Sum + Group Min", solution1);
}

long long MaximumSubarraySumWithLengthDivisibleByKSolution::maxSubarraySum(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3381
}  // namespace leetcode
