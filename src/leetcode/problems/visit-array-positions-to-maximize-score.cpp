#include "leetcode/problems/visit-array-positions-to-maximize-score.h"

namespace leetcode {
namespace problem_2786 {

// 动态规划：维护以偶数/奇数结尾的最大分数
// 时间复杂度: O(n), 空间复杂度: O(1)
static long long solution1(vector<int>& nums, int x) {
  const int n = nums.size();
  
  // even_max: 以偶数结尾的最大分数
  // odd_max: 以奇数结尾的最大分数
  // 初始化为负无穷，表示尚未访问该奇偶性的数
  long long even_max = (nums[0] % 2 == 0) ? nums[0] : LLONG_MIN / 2;
  long long odd_max = (nums[0] % 2 == 1) ? nums[0] : LLONG_MIN / 2;
  
  for (int i = 1; i < n; ++i) {
    if (nums[i] % 2 == 0) {
      // 当前是偶数：可以从偶数转移（不扣分）或从奇数转移（扣x）
      even_max = max(even_max + nums[i], odd_max + nums[i] - x);
    } else {
      // 当前是奇数：可以从奇数转移（不扣分）或从偶数转移（扣x）
      odd_max = max(odd_max + nums[i], even_max + nums[i] - x);
    }
  }
  
  return max(even_max, odd_max);
}

VisitArrayPositionsToMaximizeScoreSolution::VisitArrayPositionsToMaximizeScoreSolution() {
  setMetaInfo({
    .id = 2786,
    .title = "Visit Array Positions to Maximize Score",
    .url = "https://leetcode.com/problems/visit-array-positions-to-maximize-score/"
  });
  registerStrategy("Dynamic Programming", solution1);
}

long long VisitArrayPositionsToMaximizeScoreSolution::maxScore(vector<int>& nums, int x) {
  return getSolution()(nums, x);
}

}  // namespace problem_2786
}  // namespace leetcode
