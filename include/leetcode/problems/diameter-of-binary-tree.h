
#include "leetcode/core.h"
#include "leetcode/utils/tree.h"

namespace leetcode {
namespace problem_543 {

using Func = std::function<int(TreeNode*)>;

class DiameterOfBinaryTreeSolution : public SolutionBase<Func> {
 public:
  //! 543. Diameter of Binary Tree
  //! https://leetcode.com/problems/diameter-of-binary-tree/
  int diameterOfBinaryTree(TreeNode* root);

  DiameterOfBinaryTreeSolution();
};

}  // namespace problem_543
}  // namespace leetcode
