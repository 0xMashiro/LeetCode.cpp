#include "leetcode/core.h"

namespace leetcode {
namespace problem_897 {

using Func = std::function<TreeNode*(TreeNode*)>;

/**
 * @brief 递增顺序搜索树
 * 
 * 给定一棵二叉搜索树，重新排列树，使得最左边的节点成为树的根节点，
 * 每个节点没有左子节点，只有一个右子节点。
 */
class IncreasingOrderSearchTreeSolution : public SolutionBase<Func> {
 public:
  //! 897. Increasing Order Search Tree
  //! https://leetcode.com/problems/increasing-order-search-tree/
  TreeNode* increasingBST(TreeNode* root);

  IncreasingOrderSearchTreeSolution();
};

}  // namespace problem_897
}  // namespace leetcode
