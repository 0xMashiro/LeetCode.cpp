#include "leetcode/core.h"

namespace leetcode {
namespace problem_513 {

using Func = std::function<int(TreeNode*)>;

class FindBottomLeftTreeValueSolution : public SolutionBase<Func> {
 public:
  //! 513. Find Bottom Left Tree Value
  //! https://leetcode.com/problems/find-bottom-left-tree-value/
  int findBottomLeftValue(TreeNode* root);

  FindBottomLeftTreeValueSolution();
};

}  // namespace problem_513
}  // namespace leetcode
