#include "leetcode/problems/count-number-of-pairs-with-absolute-difference-k.h"

namespace leetcode {
namespace problem_2006 {

// 频次计数法：遍历数组，用频次数组统计已出现元素，累加 num+k 和 num-k 的计数
// 时间复杂度: O(n)，空间复杂度: O(1)（固定大小 101 的数组）
static int solution1(vector<int>& nums, int k) {
  const int MAX_VAL = 100;
  int freq[MAX_VAL + 1] = {0};
  int ans = 0;

  for (int num : nums) {
    if (num + k <= MAX_VAL) {
      ans += freq[num + k];
    }
    if (num - k >= 1) {
      ans += freq[num - k];
    }
    ++freq[num];
  }

  return ans;
}

CountNumberOfPairsWithAbsoluteDifferenceKSolution::
    CountNumberOfPairsWithAbsoluteDifferenceKSolution() {
  setMetaInfo({.id = 2006,
               .title = "Count Number of Pairs With Absolute Difference K",
               .url = "https://leetcode.com/problems/"
                      "count-number-of-pairs-with-absolute-difference-k"});
  registerStrategy({.name = "Frequency Counting",
                    .expected = "Accepted",
                    .time_complexity = "O(n)",
                    .space_complexity = "O(1)",
                    .tags = {"array", "hash-table", "counting"}},
                   solution1);
}

int CountNumberOfPairsWithAbsoluteDifferenceKSolution::countKDifference(
    vector<int>& nums, int k) {
  return getSolution()(nums, k);
}

}  // namespace problem_2006
}  // namespace leetcode
