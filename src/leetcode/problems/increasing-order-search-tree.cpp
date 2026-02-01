#include "leetcode/problems/increasing-order-search-tree.h"

namespace leetcode {
namespace problem_897 {

/**
 * 解法：中序遍历 + 重新构造
 * 思路：
 * 1. 中序遍历 BST，得到递增顺序的节点值列表
 * 2. 使用这些值重新构造只有右子节点的树
 * 
 * 时间复杂度: O(n)，需要遍历所有节点两次
 * 空间复杂度: O(n)，需要存储中序遍历结果
 */
static TreeNode* solution1(TreeNode* root) {
  if (root == nullptr) return nullptr;
  
  // 中序遍历获取所有节点值
  std::vector<int> values;
  std::function<void(TreeNode*)> inorder = [&](TreeNode* node) {
    if (node == nullptr) return;
    inorder(node->left);
    values.push_back(node->val);
    inorder(node->right);
  };
  inorder(root);
  
  // 构造新的树：只有右子节点
  TreeNode* newRoot = new TreeNode(values[0]);
  TreeNode* current = newRoot;
  for (size_t i = 1; i < values.size(); ++i) {
    current->right = new TreeNode(values[i]);
    current = current->right;
  }
  
  return newRoot;
}

/**
 * 解法：中序遍历 + 迭代实现
 * 思路：
 * 使用迭代方式中序遍历，避免递归栈开销。
 * 创建新节点构造结果树，不修改原始树。
 * 
 * 时间复杂度: O(n)
 * 空间复杂度: O(h)，迭代栈空间
 */
static TreeNode* solution2(TreeNode* root) {
  if (root == nullptr) return nullptr;
  
  std::vector<int> values;
  std::stack<TreeNode*> stk;
  TreeNode* curr = root;
  
  // 迭代中序遍历
  while (curr != nullptr || !stk.empty()) {
    while (curr != nullptr) {
      stk.push(curr);
      curr = curr->left;
    }
    curr = stk.top();
    stk.pop();
    values.push_back(curr->val);
    curr = curr->right;
  }
  
  // 构造新树
  TreeNode* newRoot = new TreeNode(values[0]);
  TreeNode* current = newRoot;
  for (size_t i = 1; i < values.size(); ++i) {
    current->right = new TreeNode(values[i]);
    current = current->right;
  }
  
  return newRoot;
}

IncreasingOrderSearchTreeSolution::IncreasingOrderSearchTreeSolution() {
  setMetaInfo({.id = 897,
               .title = "Increasing Order Search Tree",
               .url = "https://leetcode.com/problems/increasing-order-search-tree/"});
  registerStrategy("Inorder + Reconstruct", solution1);
  registerStrategy("Inorder + Relink", solution2);
}

TreeNode* IncreasingOrderSearchTreeSolution::increasingBST(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_897
}  // namespace leetcode
