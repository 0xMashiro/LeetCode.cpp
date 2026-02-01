#include "leetcode/problems/print-binary-tree.h"

namespace leetcode {
namespace problem_655 {

/**
 * @brief 计算二叉树的高度
 * @param root 根节点
 * @return 树的高度（从0开始计数）
 */
static int getHeight(TreeNode* root) {
  if (root == nullptr) return -1;
  return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

/**
 * @brief DFS填充矩阵
 * @param res 结果矩阵
 * @param root 当前节点
 * @param r 当前行
 * @param c 当前列
 * @param height 树的高度
 */
static void fillMatrix(vector<vector<string>>& res, TreeNode* root, int r, int c, int height) {
  if (root == nullptr) return;
  
  res[r][c] = std::to_string(root->val);
  
  int offset = 1 << (height - r - 1);  // 2^(height-r-1)
  
  if (root->left) {
    fillMatrix(res, root->left, r + 1, c - offset, height);
  }
  if (root->right) {
    fillMatrix(res, root->right, r + 1, c + offset, height);
  }
}

/**
 * @brief 主解决方案
 * 时间复杂度: O(n)，需要访问每个节点
 * 空间复杂度: O(h)，递归栈深度，h为树高
 */
static vector<vector<string>> solution1(TreeNode* root) {
  // 计算树的高度
  int height = getHeight(root);
  
  // 计算矩阵维度
  int m = height + 1;
  int n = (1 << (height + 1)) - 1;  // 2^(height+1) - 1
  
  // 初始化矩阵
  vector<vector<string>> res(m, vector<string>(n, ""));
  
  // 填充矩阵
  int c = (n - 1) / 2;  // 根节点的列位置
  fillMatrix(res, root, 0, c, height);
  
  return res;
}

/**
 * @brief 迭代解决方案（使用BFS）
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
 */
static vector<vector<string>> solution2(TreeNode* root) {
  int height = getHeight(root);
  int m = height + 1;
  int n = (1 << (height + 1)) - 1;
  
  vector<vector<string>> res(m, vector<string>(n, ""));
  
  // 使用队列存储 (节点, 行, 列)
  std::queue<std::tuple<TreeNode*, int, int>> q;
  q.push({root, 0, (n - 1) / 2});
  
  while (!q.empty()) {
    auto [node, r, c] = q.front();
    q.pop();
    
    if (node == nullptr) continue;
    
    res[r][c] = std::to_string(node->val);
    
    int offset = 1 << (height - r - 1);
    
    if (node->left) {
      q.push({node->left, r + 1, c - offset});
    }
    if (node->right) {
      q.push({node->right, r + 1, c + offset});
    }
  }
  
  return res;
}

PrintBinaryTreeSolution::PrintBinaryTreeSolution() {
  setMetaInfo({.id = 655,
               .title = "Print Binary Tree",
               .url = "https://leetcode.com/problems/print-binary-tree/"});
  registerStrategy("DFS Recursive", solution1);
  registerStrategy("BFS Iterative", solution2);
}

vector<vector<string>> PrintBinaryTreeSolution::printTree(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_655
}  // namespace leetcode
