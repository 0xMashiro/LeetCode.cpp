#include "leetcode/core.h"

namespace leetcode {
namespace problem_3721 {

// LeetCode 兼容的 Solution 类
class Solution {
 public:
  int longestBalanced(vector<int>& nums);
};

using Func = std::function<int(vector<int>&)>;

class LongestBalancedSubarrayIiSolution : public SolutionBase<Func> {
 public:
  int longestBalanced(vector<int>& nums);
  LongestBalancedSubarrayIiSolution();
};

}  // namespace problem_3721
}  // namespace leetcode
