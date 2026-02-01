#include "leetcode/problems/subarrays-with-k-different-integers.h"

namespace leetcode {
namespace problem_992 {

/**
 * 辅助函数：计算最多包含 k 个不同整数的子数组数量
 * 使用双指针滑动窗口算法
 * 时间复杂度: O(n), 空间复杂度: O(k)
 */
static int atMostK(vector<int>& nums, int k) {
  if (k < 0) return 0;
  
  unordered_map<int, int> freq;  // 记录窗口内每个数字的出现次数
  int left = 0;
  int count = 0;
  
  for (int right = 0; right < nums.size(); ++right) {
    // 扩展窗口：加入右端点元素
    freq[nums[right]]++;
    
    // 收缩窗口：当不同整数数量超过 k 时，移动左指针
    while (freq.size() > k) {
      freq[nums[left]]--;
      if (freq[nums[left]] == 0) {
        freq.erase(nums[left]);
      }
      left++;
    }
    
    // 以 right 为右端点的满足条件的子数组数量为 right - left + 1
    count += right - left + 1;
  }
  
  return count;
}

/**
 * 主函数：计算恰好包含 k 个不同整数的子数组数量
 * 利用转换：exactly(k) = atMost(k) - atMost(k-1)
 * 时间复杂度: O(n), 空间复杂度: O(k)
 */
static int subarraysWithKDistinctImpl(vector<int>& nums, int k) {
  return atMostK(nums, k) - atMostK(nums, k - 1);
}

SubarraysWithKDifferentIntegersSolution::SubarraysWithKDifferentIntegersSolution() {
  setMetaInfo({
    .id = 992,
    .title = "Subarrays with K Different Integers",
    .url = "https://leetcode.com/problems/subarrays-with-k-different-integers/"
  });
  registerStrategy("Sliding Window", subarraysWithKDistinctImpl);
}

int SubarraysWithKDifferentIntegersSolution::subarraysWithKDistinct(
    vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_992
}  // namespace leetcode
