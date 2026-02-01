#include "leetcode/problems/make-costs-of-paths-equal-in-a-binary-tree.h"

namespace leetcode {
namespace problem_2673 {

/**
 * 自底向上贪心算法
 * 
 * 对于完美二叉树，节点编号：
 * - 根节点：1
 * - 节点 i 的左孩子：2*i
 * - 节点 i 的右孩子：2*i+1
 * 
 * 数组 cost 是 0-indexed，所以节点 i（1-indexed）的成本是 cost[i-1]
 * 
 * 算法：
 * 1. 从最后一个非叶子节点开始（i = n/2），自底向上处理
 * 2. 对于每个节点，计算左右子树到叶子的最大路径和
 * 3. 需要增加的代价 = |左子树路径和 - 右子树路径和|
 * 4. 当前节点到叶子的路径和 = cost[i-1] + max(左子树路径和, 右子树路径和)
 * 
 * 优化：我们可以直接在 cost 数组上操作，存储从当前节点到叶子的最大路径和
 */
static int solution1(int n, vector<int>& cost) {
  long long increments = 0;
  
  // 完美二叉树的最后一个非叶子节点是 n/2（1-indexed）
  // 从最后一个非叶子节点向上遍历到根节点
  for (int i = n / 2; i >= 1; --i) {
    int leftChild = 2 * i;
    int rightChild = 2 * i + 1;
    
    // 左右子节点到叶子的路径和（已经包含了子节点自身的成本）
    // cost 数组是 0-indexed，所以节点 i 对应的索引是 i-1
    int leftSum = cost[leftChild - 1];
    int rightSum = cost[rightChild - 1];
    
    // 需要让左右子树的路径和相等，增加的代价是两者的差值
    increments += abs(leftSum - rightSum);
    
    // 当前节点到叶子的最大路径和 = 当前节点成本 + max(左子树路径和, 右子树路径和)
    cost[i - 1] += max(leftSum, rightSum);
  }
  
  return static_cast<int>(increments);
}

MakeCostsOfPathsEqualInABinaryTreeSolution::MakeCostsOfPathsEqualInABinaryTreeSolution() {
  setMetaInfo({.id = 2673,
               .title = "Make Costs of Paths Equal in a Binary Tree",
               .url = "https://leetcode.com/problems/make-costs-of-paths-equal-in-a-binary-tree/"});
  registerStrategy("Bottom-up Greedy", solution1);
}

int MakeCostsOfPathsEqualInABinaryTreeSolution::minIncrements(int n, vector<int>& cost) {
  return getSolution()(n, cost);
}

}  // namespace problem_2673
}  // namespace leetcode
