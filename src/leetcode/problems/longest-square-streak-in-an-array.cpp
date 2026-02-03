#include "leetcode/problems/longest-square-streak-in-an-array.h"

#include <cmath>

namespace leetcode {
namespace problem_2501 {

// 动态规划 + 哈希表
// 思路：对于每个数 x，如果 sqrt(x) 在数组中，则以 x 结尾的链长 = 以 sqrt(x) 结尾的链长 + 1
// 由于平方增长极快，最长链长度很小（不超过 5）
// 时间复杂度: O(n), 空间复杂度: O(n)
static int solution1(vector<int>& nums) {
  unordered_set<long long> num_set(nums.begin(), nums.end());
  unordered_map<long long, int> dp;  // 以 x 结尾的链的最大长度
  
  int max_len = 0;
  
  // 按升序处理，确保处理 x 时，sqrt(x) 已经处理过
  sort(nums.begin(), nums.end());
  
  for (int num : nums) {
    long long x = num;
    long long root = static_cast<long long>(sqrt(x));
    
    // 检查是否为完全平方数且平方根在集合中
    if (root * root == x && num_set.count(root)) {
      dp[x] = dp[root] + 1;
    } else {
      dp[x] = 1;  // 链的起点
    }
    
    max_len = max(max_len, dp[x]);
  }
  
  return max_len >= 2 ? max_len : -1;
}

LongestSquareStreakInAnArraySolution::LongestSquareStreakInAnArraySolution() {
  setMetaInfo({.id = 2501,
               .title = "Longest Square Streak in an Array",
               .url = "https://leetcode.com/problems/longest-square-streak-in-an-array/"});
  registerStrategy("DP + HashMap", solution1);
}

int LongestSquareStreakInAnArraySolution::longestSquareStreak(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2501
}  // namespace leetcode
