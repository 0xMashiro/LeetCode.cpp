
#include "leetcode/problems/balanced-binary-tree.h"

namespace leetcode {
namespace problem_110 {

/**
 * 自底向上递归判断平衡二叉树
 * 辅助函数返回子树高度，如果不平衡则返回 -1
 * 时间复杂度: O(n)，每个节点只访问一次
 * 空间复杂度: O(h)，h 为树的高度，递归栈空间
 */
static int checkHeight(TreeNode* root) {
  if (root == nullptr) {
    return 0;
  }
  
  // 递归计算左子树高度
  int leftHeight = checkHeight(root->left);
  if (leftHeight == -1) {
    return -1;  // 左子树不平衡，直接返回
  }
  
  // 递归计算右子树高度
  int rightHeight = checkHeight(root->right);
  if (rightHeight == -1) {
    return -1;  // 右子树不平衡，直接返回
  }
  
  // 检查当前节点是否平衡
  if (std::abs(leftHeight - rightHeight) > 1) {
    return -1;  // 当前节点不平衡
  }
  
  // 返回当前子树的高度
  return std::max(leftHeight, rightHeight) + 1;
}

static bool solution1(TreeNode* root) {
  return checkHeight(root) != -1;
}

BalancedBinaryTreeSolution::BalancedBinaryTreeSolution() {
  setMetaInfo({.id = 110,
               .title = "Balanced Binary Tree",
               .url = "https://leetcode.com/problems/balanced-binary-tree/"});
  registerStrategy("Bottom-up Recursion", solution1);
}

bool BalancedBinaryTreeSolution::isBalanced(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_110
}  // namespace leetcode
