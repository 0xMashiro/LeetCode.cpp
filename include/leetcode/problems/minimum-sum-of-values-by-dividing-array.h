#include "leetcode/core.h"

namespace leetcode {
namespace problem_3117 {

using Func = std::function<int(vector<int>&, vector<int>&)>;

/**
 * 3117. Minimum Sum of Values by Dividing Array
 * https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/
 *
 * 思路：动态规划 + 稀疏表
 * - 预处理区间 AND 查询（稀疏表）
 * - DP[i][j] 表示将 nums[0..i-1] 分成 j 个子数组的最小值和
 * - 转移：枚举最后一个子数组的起点 k
 * 
 * 时间复杂度：O(n^2 * log(max(nums)))，空间复杂度：O(n * m + n * log(n))
 */
class MinimumSumOfValuesByDividingArraySolution : public SolutionBase<Func> {
 public:
  int minimumValueSum(vector<int>& nums, vector<int>& andValues);

  MinimumSumOfValuesByDividingArraySolution();
};

}  // namespace problem_3117
}  // namespace leetcode
