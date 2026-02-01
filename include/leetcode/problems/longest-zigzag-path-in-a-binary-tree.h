
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1372 {

using Func = std::function<int(TreeNode*)>;

class LongestZigzagPathInABinaryTreeSolution : public SolutionBase<Func> {
 public:
  //! 1372. Longest ZigZag Path in a Binary Tree
  //! https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/
  int longestZigZag(TreeNode* root);

  LongestZigzagPathInABinaryTreeSolution();
};

}  // namespace problem_1372
}  // namespace leetcode
