#include "leetcode/problems/longest-balanced-subarray-i.h"

namespace leetcode {
namespace problem_3719 {

// 枚举左端点，向右扩展，用哈希集合统计不同偶数和奇数
// 时间复杂度: O(n^2), 空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  const int n = nums.size();
  int maxLen = 0;
  
  for (int left = 0; left < n; ++left) {
    unordered_set<int> evenSet;  // 不同偶数
    unordered_set<int> oddSet;   // 不同奇数
    
    for (int right = left; right < n; ++right) {
      if (nums[right] % 2 == 0) {
        evenSet.insert(nums[right]);
      } else {
        oddSet.insert(nums[right]);
      }
      
      // 如果不同偶数个数等于不同奇数个数，更新答案
      if (evenSet.size() == oddSet.size()) {
        maxLen = max(maxLen, right - left + 1);
      }
    }
  }
  
  return maxLen;
}

LongestBalancedSubarrayISolution::LongestBalancedSubarrayISolution() {
  setMetaInfo({.id = 3719,
               .title = "Longest Balanced Subarray I",
               .url = "https://leetcode.com/problems/longest-balanced-subarray-i/"});
  registerStrategy("Enumerate + HashSet", solution1);
}

int LongestBalancedSubarrayISolution::longestBalanced(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_3719
}  // namespace leetcode