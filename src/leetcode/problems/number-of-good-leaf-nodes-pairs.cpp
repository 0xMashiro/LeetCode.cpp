/**
 * 1530. Number of Good Leaf Nodes Pairs
 * https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/
 */

#include "leetcode/problems/number-of-good-leaf-nodes-pairs.h"

namespace leetcode {
namespace problem_1530 {

/**
 * @brief Post-order DFS solution
 * 
 * For each node, we collect distances to all leaf nodes in its subtree.
 * If current node is a leaf, return {1} (distance 1 to its parent).
 * Otherwise, recursively get distances from left and right subtrees,
 * count valid pairs where sum of distances <= target distance,
 * then return combined distances (each +1) to parent.
 */
static int solution1(TreeNode* root, int distance) {
  int result = 0;
  
  // DFS returns a vector of distances from current node to all leaf nodes
  std::function<std::vector<int>(TreeNode*)> dfs = [&](TreeNode* node) -> std::vector<int> {
    if (!node) return {};
    
    // Leaf node: return distance 1 (to its parent)
    if (!node->left && !node->right) {
      return {1};
    }
    
    // Get distances from left and right subtrees
    std::vector<int> left_distances = dfs(node->left);
    std::vector<int> right_distances = dfs(node->right);
    
    // Count valid pairs: left_dist + right_dist <= distance
    for (int ld : left_distances) {
      for (int rd : right_distances) {
        if (ld + rd <= distance) {
          result++;
        }
      }
    }
    
    // Combine distances, increment by 1 (moving up one level)
    std::vector<int> combined;
    combined.reserve(left_distances.size() + right_distances.size());
    
    for (int d : left_distances) {
      if (d + 1 <= distance) {  // Only keep distances that could form valid pairs
        combined.push_back(d + 1);
      }
    }
    for (int d : right_distances) {
      if (d + 1 <= distance) {
        combined.push_back(d + 1);
      }
    }
    
    return combined;
  };
  
  dfs(root);
  return result;
}

NumberOfGoodLeafNodesPairsSolution::NumberOfGoodLeafNodesPairsSolution() {
  setMetaInfo({.id = 1530,
               .title = "Number of Good Leaf Nodes Pairs",
               .url = "https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/"});
  registerStrategy("Post-order DFS", solution1);
}

int NumberOfGoodLeafNodesPairsSolution::countPairs(TreeNode* root, int distance) {
  return getSolution()(root, distance);
}

}  // namespace problem_1530
}  // namespace leetcode
