#include "leetcode/problems/left-and-right-sum-differences.h"

namespace leetcode {
namespace problem_2574 {

// 暴力法：对每个 i，分别计算左侧和与右侧和
// 时间复杂度: O(n²), 空间复杂度: O(1) 不计输出
static vector<int> solution1(vector<int>& nums) {
  const int n = nums.size();
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    int leftSum = 0, rightSum = 0;
    for (int j = 0; j < i; ++j) leftSum += nums[j];
    for (int j = i + 1; j < n; ++j) rightSum += nums[j];
    ans[i] = abs(leftSum - rightSum);
  }
  return ans;
}

// 前缀和法：先算总和，一遍遍历维护 leftSum
// 时间复杂度: O(n), 空间复杂度: O(1) 不计输出
static vector<int> solution2(vector<int>& nums) {
  const int n = nums.size();
  int total = 0;
  for (int v : nums) total += v;

  vector<int> ans(n);
  int leftSum = 0;
  for (int i = 0; i < n; ++i) {
    int rightSum = total - leftSum - nums[i];
    ans[i] = abs(leftSum - rightSum);
    leftSum += nums[i];
  }
  return ans;
}

LeftAndRightSumDifferencesSolution::LeftAndRightSumDifferencesSolution() {
  setMetaInfo({.id = 2574,
               .title = "Left and Right Sum Differences",
               .url = "https://leetcode.com/problems/left-and-right-sum-differences/"});
  registerStrategy({.name = "Brute Force"}, solution1);
  registerStrategy({.name = "Prefix Sum"}, solution2);
}

vector<int> LeftAndRightSumDifferencesSolution::leftRightDifference(vector<int>& nums) {
  return getSolution()(nums);
}

}  // namespace problem_2574
}  // namespace leetcode
