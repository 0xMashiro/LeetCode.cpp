
#include "leetcode/problems/balance-a-binary-search-tree.h"

namespace leetcode {
namespace problem_1382 {

// 中序遍历，收集所有节点值到数组
static void inorder(TreeNode* node, vector<int>& values) {
  if (!node) return;
  inorder(node->left, values);
  values.push_back(node->val);
  inorder(node->right, values);
}

// 用有序数组构建平衡 BST
static TreeNode* buildBalancedBST(const vector<int>& values, int left, int right) {
  if (left > right) return nullptr;
  int mid = left + (right - left) / 2;  // 防止溢出
  TreeNode* node = new TreeNode(values[mid]);
  node->left = buildBalancedBST(values, left, mid - 1);
  node->right = buildBalancedBST(values, mid + 1, right);
  return node;
}

// 主解法：中序遍历 + 重建平衡 BST
// 时间复杂度: O(n), 空间复杂度: O(n)
static TreeNode* solution1(TreeNode* root) {
  if (!root) return nullptr;
  
  vector<int> values;
  inorder(root, values);
  
  return buildBalancedBST(values, 0, values.size() - 1);
}

BalanceABinarySearchTreeSolution::BalanceABinarySearchTreeSolution() {
  setMetaInfo({.id = 1382,
               .title = "Balance a Binary Search Tree",
               .url = "https://leetcode.com/problems/balance-a-binary-search-tree/"});
  registerStrategy("Inorder + Rebuild", solution1);
}

TreeNode* BalanceABinarySearchTreeSolution::balanceBST(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_1382
}  // namespace leetcode
