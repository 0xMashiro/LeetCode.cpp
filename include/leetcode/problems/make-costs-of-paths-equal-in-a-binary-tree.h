#include "leetcode/core.h"

namespace leetcode {
namespace problem_2673 {

using Func = std::function<int(int, vector<int>&)>;

/**
 * 2673. Make Costs of Paths Equal in a Binary Tree
 * https://leetcode.com/problems/make-costs-of-paths-equal-in-a-binary-tree/
 *
 * 给定一个完美二叉树，每个节点有成本。可以增加任意节点的成本（每次+1）。
 * 求使所有根到叶子的路径成本相等的最小增量。
 *
 * 思路：自底向上的贪心
 * - 对于每个非叶子节点，需要让左右子树的路径和相等
 * - 计算从当前节点到叶子的最大路径和
 * - 记录需要增加的代价（左右子树路径和之差）
 * - 时间复杂度: O(n), 空间复杂度: O(1)（如果不算递归栈）
 */
class MakeCostsOfPathsEqualInABinaryTreeSolution : public SolutionBase<Func> {
 public:
  int minIncrements(int n, vector<int>& cost);

  MakeCostsOfPathsEqualInABinaryTreeSolution();
};

}  // namespace problem_2673
}  // namespace leetcode
