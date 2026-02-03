
#include "leetcode/problems/maximum-sum-obtained-of-any-permutation.h"

namespace leetcode {
namespace problem_1589 {

static int solution1(vector<int>& nums, vector<vector<int>>& requests) {
  const int n = nums.size();
  const int MOD = 1e9 + 7;
  
  // 使用差分数组统计每个位置被覆盖的次数
  vector<long long> diff(n + 1, 0);
  for (const auto& req : requests) {
    int start = req[0];
    int end = req[1];
    diff[start]++;
    if (end + 1 < n) {
      diff[end + 1]--;
    }
  }
  
  // 计算前缀和得到每个位置的实际覆盖次数
  vector<long long> count(n);
  long long cur = 0;
  for (int i = 0; i < n; ++i) {
    cur += diff[i];
    count[i] = cur;
  }
  
  // 将 nums 和 count 都排序
  sort(nums.begin(), nums.end(), greater<int>());
  sort(count.begin(), count.end(), greater<long long>());
  
  // 贪心：大数放在覆盖次数多的位置
  long long result = 0;
  for (int i = 0; i < n; ++i) {
    result = (result + (long long)nums[i] * count[i]) % MOD;
  }
  
  return (int)result;
}

MaximumSumObtainedOfAnyPermutationSolution::MaximumSumObtainedOfAnyPermutationSolution() {
  setMetaInfo({.id = 1589,
               .title = "Maximum Sum Obtained of Any Permutation",
               .url = "https://leetcode.com/problems/maximum-sum-obtained-of-any-permutation/"});
  registerStrategy("Greedy + Difference Array", solution1);
}

int MaximumSumObtainedOfAnyPermutationSolution::maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
  return getSolution()(nums, requests);
}

}  // namespace problem_1589
}  // namespace leetcode
