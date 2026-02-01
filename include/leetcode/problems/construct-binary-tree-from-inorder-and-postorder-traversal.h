#include "leetcode/core.h"

namespace leetcode {
namespace problem_106 {

using Func = std::function<TreeNode*(vector<int>&, vector<int>&)>;

class ConstructBinaryTreeFromInorderAndPostorderTraversalSolution : public SolutionBase<Func> {
 public:
  //! 106. Construct Binary Tree from Inorder and Postorder Traversal
  //! https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder);

  ConstructBinaryTreeFromInorderAndPostorderTraversalSolution();
};

}  // namespace problem_106
}  // namespace leetcode
