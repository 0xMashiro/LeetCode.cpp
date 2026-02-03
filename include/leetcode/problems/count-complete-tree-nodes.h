#include "leetcode/core.h"

namespace leetcode {
namespace problem_222 {

using Func = std::function<int(TreeNode*)>;

class CountCompleteTreeNodesSolution : public SolutionBase<Func> {
 public:
  //! 222. Count Complete Tree Nodes
  //! https://leetcode.com/problems/count-complete-tree-nodes/
  int countNodes(TreeNode* root);

  CountCompleteTreeNodesSolution();
};

}  // namespace problem_222
}  // namespace leetcode
