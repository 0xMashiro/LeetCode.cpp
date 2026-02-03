
#include "leetcode/problems/add-one-row-to-tree.h"

namespace leetcode {
namespace problem_623 {

// BFS 找到 depth-1 层的所有节点，然后插入新行
// 时间复杂度: O(n), 空间复杂度: O(w)，其中 w 是 depth-1 层的节点数
static TreeNode* solution1(TreeNode* root, int val, int depth) {
  if (depth == 1) {
    TreeNode* newRoot = new TreeNode(val);
    newRoot->left = root;
    return newRoot;
  }
  
  // BFS 找到 depth-1 层的所有节点
  std::queue<TreeNode*> q;
  q.push(root);
  int currentDepth = 1;
  
  while (!q.empty() && currentDepth < depth - 1) {
    int size = q.size();
    for (int i = 0; i < size; ++i) {
      TreeNode* node = q.front();
      q.pop();
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }
    currentDepth++;
  }
  
  // 现在 q 中就是 depth-1 层的所有节点
  while (!q.empty()) {
    TreeNode* node = q.front();
    q.pop();
    
    // 保存原来的左右子树
    TreeNode* originalLeft = node->left;
    TreeNode* originalRight = node->right;
    
    // 创建新的左右子节点
    node->left = new TreeNode(val);
    node->right = new TreeNode(val);
    
    // 将原来的子树挂到新节点下
    node->left->left = originalLeft;
    node->right->right = originalRight;
  }
  
  return root;
}

AddOneRowToTreeSolution::AddOneRowToTreeSolution() {
  setMetaInfo({.id = 623,
               .title = "Add One Row to Tree",
               .url = "https://leetcode.com/problems/add-one-row-to-tree/"});
  registerStrategy("BFS", solution1);
}

TreeNode* AddOneRowToTreeSolution::addOneRow(TreeNode* root, int val, int depth) {
  return getSolution()(root, val, depth);
}

}  // namespace problem_623
}  // namespace leetcode
