#include "leetcode/problems/convert-bst-to-greater-tree.h"

namespace leetcode {
namespace problem_538 {

// 反向中序遍历实现
// 先遍历右子树，再处理当前节点，最后遍历左子树
static TreeNode* solution1(TreeNode* root) {
  int sum = 0;
  
  std::function<void(TreeNode*)> reverseInorder = [&](TreeNode* node) {
    if (node == nullptr) return;
    
    // 1. 先遍历右子树（值更大的节点）
    reverseInorder(node->right);
    
    // 2. 处理当前节点
    sum += node->val;
    node->val = sum;
    
    // 3. 遍历左子树（值更小的节点）
    reverseInorder(node->left);
  };
  
  reverseInorder(root);
  return root;
}

// 迭代版本实现（使用栈）
static TreeNode* solution2(TreeNode* root) {
  int sum = 0;
  TreeNode* node = root;
  std::vector<TreeNode*> stack;
  
  // 反向中序遍历：Right-Root-Left
  while (node != nullptr || !stack.empty()) {
    // 走到最右边
    while (node != nullptr) {
      stack.push_back(node);
      node = node->right;
    }
    
    // 处理当前节点
    node = stack.back();
    stack.pop_back();
    sum += node->val;
    node->val = sum;
    
    // 转向左子树
    node = node->left;
  }
  
  return root;
}

ConvertBstToGreaterTreeSolution::ConvertBstToGreaterTreeSolution() {
  setMetaInfo({
    .id = 538,
    .title = "Convert BST to Greater Tree",
    .url = "https://leetcode.com/problems/convert-bst-to-greater-tree/"
  });
  registerStrategy("Recursive Reverse Inorder", solution1);
  registerStrategy("Iterative Reverse Inorder", solution2);
}

TreeNode* ConvertBstToGreaterTreeSolution::convertBST(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_538
}  // namespace leetcode
