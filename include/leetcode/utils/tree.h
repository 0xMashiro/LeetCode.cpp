#ifndef LEETCODE_UTILS_TREE_H__
#define LEETCODE_UTILS_TREE_H__

#include <optional>
#include <vector>

namespace leetcode {
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}

  ~TreeNode() {
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
  }
};

//! Construct a tree from a vector in level order.
//! Note: value -1 means null.
TreeNode* constructTree(std::vector<int> values);

TreeNode* constructTree(std::vector<std::optional<int>> values);

//! Traverse a tree in preorder.
//! Root -> Left -> Right
std::vector<int> preorderTraversal(TreeNode* root);

//! Traverse a tree in inorder.
//! Left -> Root -> Right
std::vector<int> inorderTraversal(TreeNode* root);

//! Traverse a tree in postorder.
//! Left -> Right -> Root
std::vector<int> postorderTraversal(TreeNode* root);

//! Traverse a tree in level order, return a vector.
std::vector<int> levelOrderTraversal(TreeNode* root);

//! Traverse a tree in level order, return a vector of each level.
std::vector<std::vector<int>> levelOrder(TreeNode* root);

//! invert a tree
TreeNode* invertTree(TreeNode* root);

//! compare two trees
bool isSameTree(TreeNode* p, TreeNode* q);

//! check if a tree is a binary search tree
bool isBST(TreeNode* root);

//! check if a tree is a balanced binary search tree
bool isBBST(TreeNode* root);
}  // namespace leetcode
#endif  // LEETCODE_UTILS_TREE_H__