#include "leetcode/problems/sum-root-to-leaf-numbers.h"

namespace leetcode {
namespace problem_129 {

/**
 * @brief DFS 解法
 * 时间复杂度: O(n)，每个节点访问一次
 * 空间复杂度: O(h)，h 为树高度，递归栈空间
 */
static int solution1(TreeNode* root) {
  if (!root) return 0;

  int totalSum = 0;

  std::function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int current) {
    if (!node) return;

    // 更新当前路径代表的数字
    current = current * 10 + node->val;

    // 到达叶子节点，加入总和
    if (!node->left && !node->right) {
      totalSum += current;
      return;
    }

    // 继续遍历左右子树
    dfs(node->left, current);
    dfs(node->right, current);
  };

  dfs(root, 0);
  return totalSum;
}

/**
 * @brief 迭代解法（使用栈模拟 DFS）
 * 时间复杂度: O(n)
 * 空间复杂度: O(h)
 */
static int solution2(TreeNode* root) {
  if (!root) return 0;

  int totalSum = 0;
  // 栈存储 {节点, 当前路径数字}
  std::stack<std::pair<TreeNode*, int>> stk;
  stk.push({root, 0});

  while (!stk.empty()) {
    auto [node, current] = stk.top();
    stk.pop();

    // 更新当前路径代表的数字
    current = current * 10 + node->val;

    // 到达叶子节点，加入总和
    if (!node->left && !node->right) {
      totalSum += current;
      continue;
    }

    // 子节点入栈
    if (node->right) stk.push({node->right, current});
    if (node->left) stk.push({node->left, current});
  }

  return totalSum;
}

SumRootToLeafNumbersSolution::SumRootToLeafNumbersSolution() {
  setMetaInfo({.id = 129,
               .title = "Sum Root to Leaf Numbers",
               .url = "https://leetcode.com/problems/sum-root-to-leaf-numbers/"});
  registerStrategy("DFS Recursive", solution1);
  registerStrategy("DFS Iterative", solution2);
}

int SumRootToLeafNumbersSolution::sumNumbers(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_129
}  // namespace leetcode
