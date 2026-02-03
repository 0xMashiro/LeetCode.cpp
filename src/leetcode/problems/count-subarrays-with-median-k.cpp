#include "leetcode/problems/count-subarrays-with-median-k.h"

namespace leetcode {
namespace problem_2488 {

// 转换 + 前缀和 + 哈希表
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution(vector<int>& nums, int k) {
  const int n = nums.size();
  
  // 找到 k 的位置
  int pos = -1;
  for (int i = 0; i < n; ++i) {
    if (nums[i] == k) {
      pos = i;
      break;
    }
  }
  
  // 计算左侧前缀和及其出现次数
  // key: 前缀和, value: 出现次数
  unordered_map<int, int> leftCount;
  int sum = 0;
  leftCount[0] = 1;  // 空前缀，和为0
  
  // 从 pos-1 向左遍历
  for (int i = pos - 1; i >= 0; --i) {
    if (nums[i] > k) {
      sum += 1;
    } else {
      sum -= 1;
    }
    leftCount[sum]++;
  }
  
  // 计算答案
  // 只包含 k 的子数组 [k]
  int ans = leftCount[0];  // sum=0，即左边界为空
  
  // 计算只包含左侧+k（不包含右侧）的子数组
  // 右侧为空，右侧sum=0，需要左侧sum=0或1
  // sum=0 的情况已经统计（只包含k）
  // sum=1 的情况：lessCnt = greaterCnt - 1（偶数长度）
  if (leftCount.find(1) != leftCount.end()) {
    ans += leftCount[1];
  }
  
  // 向右遍历，找右端点（包含右侧元素的子数组）
  sum = 0;
  for (int i = pos + 1; i < n; ++i) {
    if (nums[i] > k) {
      sum += 1;
    } else {
      sum -= 1;
    }
    // 需要左侧前缀和为 -sum 或 1-sum
    // 子数组和 = 左侧和 + 右侧和 = 0 或 1
    int need1 = -sum;      // 和为 0（奇数长度）
    int need2 = 1 - sum;   // 和为 1（偶数长度）
    if (leftCount.find(need1) != leftCount.end()) {
      ans += leftCount[need1];
    }
    if (leftCount.find(need2) != leftCount.end()) {
      ans += leftCount[need2];
    }
  }
  
  return ans;
}

CountSubarraysWithMedianKSolution::CountSubarraysWithMedianKSolution() {
  setMetaInfo({.id = 2488,
               .title = "Count Subarrays With Median K",
               .url = "https://leetcode.com/problems/count-subarrays-with-median-k/"});
  registerStrategy("Prefix Sum + Hash", solution);
}

int CountSubarraysWithMedianKSolution::countSubarrays(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_2488
}  // namespace leetcode