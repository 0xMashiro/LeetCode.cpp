#include "leetcode/core.h"

namespace leetcode {
namespace problem_1038 {

using Func = std::function<TreeNode*(TreeNode*)>;

/**
 * @brief Binary Search Tree to Greater Sum Tree
 * @details Given the root of a Binary Search Tree (BST), convert it to a 
 *          Greater Tree such that every key of the original BST is changed 
 *          to the original key plus the sum of all keys greater than the 
 *          original key in BST.
 *
 * Approach: Reverse Inorder Traversal (Right-Root-Left)
 * - In a BST, inorder traversal gives ascending order
 * - Reverse inorder traversal gives descending order
 * - Maintain a running sum, add it to each node's value
 * 
 * Time Complexity: O(n), where n is the number of nodes
 * Space Complexity: O(h), where h is the height of the tree (recursion stack)
 */
class BinarySearchTreeToGreaterSumTreeSolution : public SolutionBase<Func> {
 public:
  TreeNode* bstToGst(TreeNode* root);

  BinarySearchTreeToGreaterSumTreeSolution();
};

}  // namespace problem_1038
}  // namespace leetcode
