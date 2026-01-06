#include "leetcode/core.h"

namespace leetcode {
namespace problem_1161 {

using Func = std::function<int(TreeNode*)>;

class MaximumLevelSumOfABinaryTreeSolution : public SolutionBase<Func> {
 public:
  //! 1161. Maximum Level Sum of a Binary Tree
  //! https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
  int maxLevelSum(TreeNode* root);

  MaximumLevelSumOfABinaryTreeSolution();
};

}  // namespace problem_1161
}  // namespace leetcode