#include "leetcode/core.h"

namespace leetcode {
namespace problem_3533 {

using Func = std::function<vector<int>(vector<int>&, int)>;

/**
 * Concatenated Divisibility
 * https://leetcode.com/problems/concatenated-divisibility/
 * 
 * 状态压缩DP：dp[mask][rem] 表示使用mask中的数字、余数为rem时的最优序列
 * 由于需要字典序最小，使用BFS或迭代DP时按数字从小到大枚举
 */
class ConcatenatedDivisibilitySolution : public SolutionBase<Func> {
 public:
  vector<int> concatenatedDivisibility(vector<int>& nums, int k);

  ConcatenatedDivisibilitySolution();
};

}  // namespace problem_3533
}  // namespace leetcode
