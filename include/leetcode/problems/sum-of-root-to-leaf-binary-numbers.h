#include "leetcode/core.h"

namespace leetcode {
namespace problem_1022 {

using Func = std::function<int(TreeNode*)>;

class SumOfRootToLeafBinaryNumbersSolution : public SolutionBase<Func> {
 public:
  int sumRootToLeaf(TreeNode* root);

  SumOfRootToLeafBinaryNumbersSolution();
};

}  // namespace problem_1022
}  // namespace leetcode