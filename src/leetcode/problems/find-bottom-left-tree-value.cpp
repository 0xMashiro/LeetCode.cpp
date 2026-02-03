#include "leetcode/problems/find-bottom-left-tree-value.h"

namespace leetcode {
namespace problem_513 {

// BFS（层序遍历）：遍历每层，记录每层第一个节点
// 时间复杂度: O(n), 空间复杂度: O(w)，w为树的最大宽度
static int solution1(TreeNode* root) {
  if (!root) return 0;
  
  std::queue<TreeNode*> queue;
  queue.push(root);
  int leftmost_value = root->val;
  
  while (!queue.empty()) {
    int level_size = queue.size();
    for (int i = 0; i < level_size; ++i) {
      TreeNode* node = queue.front();
      queue.pop();
      // 每层第一个节点
      if (i == 0) {
        leftmost_value = node->val;
      }
      if (node->left) queue.push(node->left);
      if (node->right) queue.push(node->right);
    }
  }
  
  return leftmost_value;
}

// DFS（深度优先搜索）：先遍历左子树，记录最大深度对应的节点值
// 时间复杂度: O(n), 空间复杂度: O(h)，h为树的高度
static int solution2(TreeNode* root) {
  int max_depth = -1;
  int result = 0;
  
  std::function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int depth) {
    if (!node) return;
    // 先访问左子树，所以当遇到更深的节点时，一定是该层最左边的
    if (depth > max_depth) {
      max_depth = depth;
      result = node->val;
    }
    dfs(node->left, depth + 1);
    dfs(node->right, depth + 1);
  };
  
  dfs(root, 0);
  return result;
}

FindBottomLeftTreeValueSolution::FindBottomLeftTreeValueSolution() {
  setMetaInfo({.id = 513,
               .title = "Find Bottom Left Tree Value",
               .url = "https://leetcode.com/problems/find-bottom-left-tree-value/"});
  registerStrategy("BFS", solution1);
  registerStrategy("DFS", solution2);
}

int FindBottomLeftTreeValueSolution::findBottomLeftValue(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_513
}  // namespace leetcode
