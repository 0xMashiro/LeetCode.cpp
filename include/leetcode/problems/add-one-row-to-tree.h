
#include "leetcode/core.h"

namespace leetcode {
namespace problem_623 {

using Func = std::function<TreeNode*(TreeNode*, int, int)>;

class AddOneRowToTreeSolution : public SolutionBase<Func> {
 public:
  //! 623. Add One Row to Tree
  //! https://leetcode.com/problems/add-one-row-to-tree/
  TreeNode* addOneRow(TreeNode* root, int val, int depth);

  AddOneRowToTreeSolution();
};

}  // namespace problem_623
}  // namespace leetcode
