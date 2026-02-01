#include "leetcode/problems/vertical-order-traversal-of-a-binary-tree.h"

namespace leetcode {
namespace problem_987 {

// BFS + 排序
// 时间复杂度: O(n log n), 空间复杂度: O(n)
// 使用 map 按列和行组织节点，同一位置的节点按值排序
static vector<vector<int>> solution1(TreeNode* root) {
  if (root == nullptr) return {};
  
  // map<col, map<row, multiset<val>>>
  // 列 -> 行 -> 该位置的所有值（自动按值排序）
  map<int, map<int, multiset<int>>> nodes;
  
  // BFS 遍历，记录每个节点的坐标
  queue<pair<TreeNode*, pair<int, int>>> q;  // {node, {row, col}}
  q.push({root, {0, 0}});
  
  while (!q.empty()) {
    auto [node, pos] = q.front();
    q.pop();
    int row = pos.first;
    int col = pos.second;
    
    nodes[col][row].insert(node->val);
    
    if (node->left) {
      q.push({node->left, {row + 1, col - 1}});
    }
    if (node->right) {
      q.push({node->right, {row + 1, col + 1}});
    }
  }
  
  // 组织结果
  vector<vector<int>> result;
  for (auto& [col, rowMap] : nodes) {
    vector<int> colValues;
    for (auto& [row, values] : rowMap) {
      colValues.insert(colValues.end(), values.begin(), values.end());
    }
    result.push_back(colValues);
  }
  
  return result;
}

// DFS 版本
// 时间复杂度: O(n log n), 空间复杂度: O(n)
static vector<vector<int>> solution2(TreeNode* root) {
  if (root == nullptr) return {};
  
  map<int, map<int, multiset<int>>> nodes;
  
  function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int row, int col) {
    if (node == nullptr) return;
    nodes[col][row].insert(node->val);
    dfs(node->left, row + 1, col - 1);
    dfs(node->right, row + 1, col + 1);
  };
  
  dfs(root, 0, 0);
  
  vector<vector<int>> result;
  for (auto& [col, rowMap] : nodes) {
    vector<int> colValues;
    for (auto& [row, values] : rowMap) {
      colValues.insert(colValues.end(), values.begin(), values.end());
    }
    result.push_back(colValues);
  }
  
  return result;
}

VerticalOrderTraversalOfABinaryTreeSolution::VerticalOrderTraversalOfABinaryTreeSolution() {
  setMetaInfo({.id = 987,
               .title = "Vertical Order Traversal of a Binary Tree",
               .url = "https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/"});
  registerStrategy("BFS + Sorting", solution1);
  registerStrategy("DFS + Sorting", solution2);
}

vector<vector<int>> VerticalOrderTraversalOfABinaryTreeSolution::verticalTraversal(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_987
}  // namespace leetcode
