#include "leetcode/core.h"

namespace leetcode {
namespace problem_129 {

using Func = std::function<int(TreeNode*)>;

/**
 * @brief 129. Sum Root to Leaf Numbers
 * @details Given the root of a binary tree containing digits from 0 to 9 only.
 * Each root-to-leaf path represents a number. Return the total sum.
 * https://leetcode.com/problems/sum-root-to-leaf-numbers/
 */
class SumRootToLeafNumbersSolution : public SolutionBase<Func> {
 public:
  int sumNumbers(TreeNode* root);

  SumRootToLeafNumbersSolution();
};

}  // namespace problem_129
}  // namespace leetcode
