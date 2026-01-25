#include "leetcode/problems/minimum-difference-between-highest-and-lowest-of-k-scores.h"

namespace leetcode {
namespace problem_1984 {

// 排序 + 滑动窗口
// 思路：先对数组排序，然后遍历每个长度为 k 的连续子数组，计算差值
// 时间复杂度: O(n log n), 空间复杂度: O(log n)（排序使用的栈空间）
static int solution1(vector<int>& nums, int k) {
  sort(nums.begin(), nums.end());
  int n = nums.size();
  int minDiff = INT_MAX;
  for (int i = 0; i <= n - k; ++i) {
    int diff = nums[i + k - 1] - nums[i];
    if (diff < minDiff) {
      minDiff = diff;
    }
  }
  return minDiff;
}

MinimumDifferenceBetweenHighestAndLowestOfKScoresSolution::MinimumDifferenceBetweenHighestAndLowestOfKScoresSolution() {
  setMetaInfo({.id = 1984,
               .title = "Minimum Difference Between Highest and Lowest of K Scores",
               .url = "https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/"});
  registerStrategy("Sorting + Sliding Window", solution1);
}

int MinimumDifferenceBetweenHighestAndLowestOfKScoresSolution::minimumDifference(vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_1984
}  // namespace leetcode