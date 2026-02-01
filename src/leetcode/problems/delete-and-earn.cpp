#include "leetcode/problems/delete-and-earn.h"

namespace leetcode {
namespace problem_740 {

/**
 * 动态规划解法
 * 思路：
 * 1. 统计每个数字出现的次数，计算每个数字能获得的总分数
 * 2. 问题转化为打家劫舍问题：不能选择相邻数字
 * 3. dp[i] = max(dp[i-1], dp[i-2] + total[i])
 * 
 * 时间复杂度: O(n + max(nums)), 其中 n 是 nums 长度
 * 空间复杂度: O(max(nums))
 */
static int solution1(vector<int>& nums) {
  if (nums.empty()) return 0;
  
  // 找到最大值
  int maxNum = 0;
  for (int num : nums) {
    maxNum = max(maxNum, num);
  }
  
  // 统计每个数字的总分数
  vector<int> total(maxNum + 1, 0);
  for (int num : nums) {
    total[num] += num;
  }
  
  // 动态规划：dp[i] 表示考虑到数字 i 时的最大分数
  // 使用滚动数组优化空间
  int prev2 = 0;  // dp[i-2]
  int prev1 = total[0];  // dp[i-1]
  
  for (int i = 1; i <= maxNum; ++i) {
    int curr = max(prev1, prev2 + total[i]);
    prev2 = prev1;
    prev1 = curr;
  }
  
  return prev1;
}

/**
 * 优化空间版本：直接在 total 数组上进行 DP
 */
static int solution2(vector<int>& nums) {
  if (nums.empty()) return 0;
  
  int maxNum = 0;
  for (int num : nums) {
    maxNum = max(maxNum, num);
  }
  
  vector<int> total(maxNum + 1, 0);
  for (int num : nums) {
    total[num] += num;
  }
  
  // 如果只有一个数字
  if (maxNum == 0) return total[0];
  
  // dp[i] = max(dp[i-1], dp[i-2] + total[i])
  int take = total[0];      // dp[i-2]
  int skip = max(total[0], total[1]);  // dp[i-1]
  
  for (int i = 2; i <= maxNum; ++i) {
    int curr = max(skip, take + total[i]);
    take = skip;
    skip = curr;
  }
  
  return skip;
}

DeleteAndEarnSolution::DeleteAndEarnSolution() {
  setMetaInfo({.id = 740,
               .title = "Delete and Earn",
               .url = "https://leetcode.com/problems/delete-and-earn/"});
  registerStrategy("DP with Rolling Array", solution1);
  registerStrategy("DP Optimized", solution2);
}

int DeleteAndEarnSolution::deleteAndEarn(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_740
}  // namespace leetcode
