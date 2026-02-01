#include "leetcode/core.h"

namespace leetcode {
namespace problem_1325 {

using Func = std::function<TreeNode*(TreeNode*, int)>;

class DeleteLeavesWithAGivenValueSolution : public SolutionBase<Func> {
 public:
  //! 1325. Delete Leaves With a Given Value
  //! https://leetcode.com/problems/delete-leaves-with-a-given-value/
  TreeNode* removeLeafNodes(TreeNode* root, int target);

  DeleteLeavesWithAGivenValueSolution();
};

}  // namespace problem_1325
}  // namespace leetcode
