#include "leetcode/problems/sum-of-root-to-leaf-binary-numbers.h"

namespace leetcode {
namespace problem_1022 {

// DFS 递归解法
// 时间复杂度: O(n)，遍历每个节点一次
// 空间复杂度: O(h)，递归栈深度为树的高度
static int dfs(TreeNode* node, int current) {
  if (node == nullptr) return 0;
  
  // 当前路径的二进制值 = 之前的值 * 2 + 当前节点值
  current = current * 2 + node->val;
  
  // 叶子节点：返回当前路径的值
  if (node->left == nullptr && node->right == nullptr) {
    return current;
  }
  
  // 非叶子节点：递归计算左右子树的路径和
  return dfs(node->left, current) + dfs(node->right, current);
}

static int solution1(TreeNode* root) {
  return dfs(root, 0);
}

SumOfRootToLeafBinaryNumbersSolution::SumOfRootToLeafBinaryNumbersSolution() {
  setMetaInfo({.id = 1022,
               .title = "Sum of Root To Leaf Binary Numbers",
               .url = "https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/"});
  registerStrategy("DFS Recursive", solution1);
}

int SumOfRootToLeafBinaryNumbersSolution::sumRootToLeaf(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_1022
}  // namespace leetcode