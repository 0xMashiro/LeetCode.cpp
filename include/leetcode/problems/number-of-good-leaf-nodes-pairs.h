/**
 * 1530. Number of Good Leaf Nodes Pairs
 * https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/
 *
 * You are given the root of a binary tree and an integer distance. A pair of
 * two different leaf nodes of a binary tree is said to be good if the length
 * of the shortest path between them is less than or equal to distance.
 *
 * Return the number of good leaf node pairs in the tree.
 */

#include "leetcode/core.h"

namespace leetcode {
namespace problem_1530 {

using Func = std::function<int(TreeNode*, int)>;

/**
 * @brief Solution for 1530. Number of Good Leaf Nodes Pairs
 *
 * Approach: Post-order DFS
 * For each node, return a list of distances from this node to all leaf nodes
 * in its subtree. Then count pairs where left_dist + right_dist <= distance.
 *
 * Time Complexity: O(n * d^2) where n is number of nodes, d is distance
 * Space Complexity: O(h * d) where h is tree height
 */
class NumberOfGoodLeafNodesPairsSolution : public SolutionBase<Func> {
 public:
  //! 1530. Number of Good Leaf Nodes Pairs
  //! https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/
  int countPairs(TreeNode* root, int distance);

  NumberOfGoodLeafNodesPairsSolution();
};

}  // namespace problem_1530
}  // namespace leetcode
