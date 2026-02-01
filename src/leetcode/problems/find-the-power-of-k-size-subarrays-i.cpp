
#include "leetcode/problems/find-the-power-of-k-size-subarrays-i.h"

namespace leetcode {
namespace problem_3254 {

// 滑动窗口：遍历所有长度为 k 的子数组
// 对每个子数组，检查是否连续且升序（相邻差值为1）
// 时间复杂度: O(n*k), 空间复杂度: O(1)（除结果外）
static vector<int> solution1(vector<int>& nums, int k) {
  const int n = nums.size();
  vector<int> results;
  results.reserve(n - k + 1);
  
  for (int i = 0; i <= n - k; ++i) {
    bool isConsecutive = true;
    // 检查子数组 nums[i..i+k-1] 是否连续且升序
    for (int j = i; j < i + k - 1; ++j) {
      if (nums[j + 1] - nums[j] != 1) {
        isConsecutive = false;
        break;
      }
    }
    
    if (isConsecutive) {
      // 连续且升序，power = 最大值（即最后一个元素）
      results.push_back(nums[i + k - 1]);
    } else {
      // 不连续或不是升序，power = -1
      results.push_back(-1);
    }
  }
  
  return results;
}

FindThePowerOfKSizeSubarraysISolution::FindThePowerOfKSizeSubarraysISolution() {
  setMetaInfo({.id = 3254,
               .title = "Find the Power of K-Size Subarrays I",
               .url = "https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/"});
  registerStrategy("Sliding Window", solution1);
}

vector<int> FindThePowerOfKSizeSubarraysISolution::resultsArray(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_3254
}  // namespace leetcode
