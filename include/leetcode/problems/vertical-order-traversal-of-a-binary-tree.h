#include "leetcode/core.h"

namespace leetcode {
namespace problem_987 {

using Func = std::function<vector<vector<int>>(TreeNode*)>;

class VerticalOrderTraversalOfABinaryTreeSolution : public SolutionBase<Func> {
 public:
  //! 987. Vertical Order Traversal of a Binary Tree
  //! https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/
  vector<vector<int>> verticalTraversal(TreeNode* root);

  VerticalOrderTraversalOfABinaryTreeSolution();
};

}  // namespace problem_987
}  // namespace leetcode
