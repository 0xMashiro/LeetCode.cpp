#include "leetcode/problems/subarrays-distinct-element-sum-of-squares-i.h"

namespace leetcode {
namespace problem_2913 {

// 暴力枚举：枚举所有子数组，用哈希集合统计不同元素个数
// 时间复杂度: O(n²), 空间复杂度: O(n)
// 由于 n <= 100，暴力方法是足够的
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  long long result = 0;  // 使用 long long 防止溢出
  
  for (int i = 0; i < n; ++i) {
    unordered_set<int> distinct;  // 存储当前子数组的不同元素
    for (int j = i; j < n; ++j) {
      distinct.insert(nums[j]);  // 加入当前元素
      int count = distinct.size();  // 不同元素个数
      result += 1LL * count * count;  // 累加平方
    }
  }
  
  return static_cast<int>(result);
}

SubarraysDistinctElementSumOfSquaresISolution::SubarraysDistinctElementSumOfSquaresISolution() {
  setMetaInfo({.id = 2913,
               .title = "Subarrays Distinct Element Sum of Squares I",
               .url = "https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/"});
  registerStrategy("Brute Force", solution1);
}

int SubarraysDistinctElementSumOfSquaresISolution::sumCounts(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2913
}  // namespace leetcode
