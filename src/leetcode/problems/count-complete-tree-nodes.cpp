#include "leetcode/problems/count-complete-tree-nodes.h"

namespace leetcode {
namespace problem_222 {

// 计算左子树高度（一直往左走）
static int leftHeight(TreeNode* root) {
  int height = 0;
  while (root != nullptr) {
    height++;
    root = root->left;
  }
  return height;
}

// 计算右子树高度（一直往右走）
static int rightHeight(TreeNode* root) {
  int height = 0;
  while (root != nullptr) {
    height++;
    root = root->right;
  }
  return height;
}

// 解法：利用完全二叉树性质递归求解
// 时间复杂度: O((log n)²), 空间复杂度: O(log n)
static int solution1(TreeNode* root) {
  if (root == nullptr) return 0;
  
  int leftH = leftHeight(root);
  int rightH = rightHeight(root);
  
  // 如果左右高度相等，左子树是满的，节点数为 2^leftH - 1，加上根节点为 2^leftH
  if (leftH == rightH) {
    return (1 << leftH) - 1;
  }
  
  // 高度不等，分别递归计算左右子树
  return 1 + solution1(root->left) + solution1(root->right);
}

CountCompleteTreeNodesSolution::CountCompleteTreeNodesSolution() {
  setMetaInfo({.id = 222,
               .title = "Count Complete Tree Nodes",
               .url = "https://leetcode.com/problems/count-complete-tree-nodes/"});
  registerStrategy("Divide and Conquer", solution1);
}

int CountCompleteTreeNodesSolution::countNodes(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_222
}  // namespace leetcode
