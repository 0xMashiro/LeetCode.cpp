#include "leetcode/core.h"

namespace leetcode {
namespace problem_655 {

using Func = std::function<vector<vector<string>>(TreeNode*)>;

/**
 * @brief 打印二叉树解决方案
 * 
 * 给定二叉树根节点，构造一个 m x n 的字符串矩阵表示格式化的树布局
 * - 行数 m = height + 1
 * - 列数 n = 2^(height+1) - 1
 * - 根节点放在第一行中间
 * - 左右子节点按照规则放置在下一行
 */
class PrintBinaryTreeSolution : public SolutionBase<Func> {
 public:
  //! 655. Print Binary Tree
  //! https://leetcode.com/problems/print-binary-tree/
  vector<vector<string>> printTree(TreeNode* root);

  PrintBinaryTreeSolution();
};

}  // namespace problem_655
}  // namespace leetcode
