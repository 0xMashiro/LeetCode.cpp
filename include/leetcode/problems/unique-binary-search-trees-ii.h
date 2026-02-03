#include "leetcode/core.h"

namespace leetcode {
namespace problem_95 {

using Func = std::function<vector<TreeNode*>(int)>;

/**
 * @brief Unique Binary Search Trees II
 * https://leetcode.com/problems/unique-binary-search-trees-ii/
 * 
 * Given an integer n, return all the structurally unique BST's (binary search trees),
 * which has exactly n nodes of unique values from 1 to n.
 */
class UniqueBinarySearchTreesIiSolution : public SolutionBase<Func> {
 public:
  vector<TreeNode*> generateTrees(int n);
  
  UniqueBinarySearchTreesIiSolution();
};

}  // namespace problem_95
}  // namespace leetcode
