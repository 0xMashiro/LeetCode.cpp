
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1382 {

using Func = std::function<TreeNode*(TreeNode*)>;

class BalanceABinarySearchTreeSolution : public SolutionBase<Func> {
 public:
  //! 1382. Balance a Binary Search Tree
  //! https://leetcode.com/problems/balance-a-binary-search-tree/
  TreeNode* balanceBST(TreeNode* root);

  BalanceABinarySearchTreeSolution();
};

}  // namespace problem_1382
}  // namespace leetcode
