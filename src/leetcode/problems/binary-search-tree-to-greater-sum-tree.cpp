#include "leetcode/problems/binary-search-tree-to-greater-sum-tree.h"

namespace leetcode {
namespace problem_1038 {

/**
 * @brief Convert BST to Greater Tree using reverse inorder traversal
 * 
 * Key insight: In a BST, all nodes in the right subtree are greater than 
 * the current node. So we traverse in reverse inorder (right-root-left)
 * to visit nodes in descending order, accumulating the sum as we go.
 */
static TreeNode* solution1(TreeNode* root) {
  int sum = 0;
  
  std::function<void(TreeNode*)> reverseInorder = [&](TreeNode* node) {
    if (node == nullptr) return;
    
    // First, visit the right subtree (all greater values)
    reverseInorder(node->right);
    
    // Update current node: add accumulated sum to current value
    sum += node->val;
    node->val = sum;
    
    // Then, visit the left subtree (all smaller values)
    reverseInorder(node->left);
  };
  
  reverseInorder(root);
  return root;
}

/**
 * @brief Iterative version using explicit stack
 * 
 * Same logic as the recursive solution, but uses an explicit stack
 * to avoid recursion depth issues for very deep trees.
 */
static TreeNode* solution2(TreeNode* root) {
  if (root == nullptr) return nullptr;
  
  int sum = 0;
  TreeNode* current = root;
  std::vector<TreeNode*> stack;
  
  // Reverse inorder: right-root-left
  while (current != nullptr || !stack.empty()) {
    // Push all right nodes to stack
    while (current != nullptr) {
      stack.push_back(current);
      current = current->right;
    }
    
    // Process the top node
    current = stack.back();
    stack.pop_back();
    
    // Update with accumulated sum
    sum += current->val;
    current->val = sum;
    
    // Move to left subtree
    current = current->left;
  }
  
  return root;
}

BinarySearchTreeToGreaterSumTreeSolution::BinarySearchTreeToGreaterSumTreeSolution() {
  setMetaInfo({
    .id = 1038,
    .title = "Binary Search Tree to Greater Sum Tree",
    .url = "https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/"
  });
  registerStrategy("Recursive Reverse Inorder", solution1);
  registerStrategy("Iterative Reverse Inorder", solution2);
}

TreeNode* BinarySearchTreeToGreaterSumTreeSolution::bstToGst(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_1038
}  // namespace leetcode
