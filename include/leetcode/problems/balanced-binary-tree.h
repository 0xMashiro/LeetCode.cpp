
#include "leetcode/core.h"

namespace leetcode {
namespace problem_110 {

using Func = std::function<bool(TreeNode*)>;

class BalancedBinaryTreeSolution : public SolutionBase<Func> {
 public:
  //! 110. Balanced Binary Tree
  //! https://leetcode.com/problems/balanced-binary-tree/
  bool isBalanced(TreeNode* root);

  BalancedBinaryTreeSolution();
};

}  // namespace problem_110
}  // namespace leetcode
