#include "leetcode/core.h"

namespace leetcode {
namespace problem_538 {

using Func = std::function<TreeNode*(TreeNode*)>;

/**
 * @brief 将BST转换为累加树
 * 
 * 思路：反向中序遍历（Right-Root-Left）
 * - 正常中序遍历（Left-Root-Right）得到升序序列
 * - 反向中序遍历（Right-Root-Left）得到降序序列
 * - 在遍历过程中维护累加和，每个节点值加上累加和
 * 
 * 时间复杂度: O(n)，每个节点访问一次
 * 空间复杂度: O(h)，递归栈空间，h为树高度
 */
class ConvertBstToGreaterTreeSolution : public SolutionBase<Func> {
 public:
  TreeNode* convertBST(TreeNode* root);

  ConvertBstToGreaterTreeSolution();
};

}  // namespace problem_538
}  // namespace leetcode
