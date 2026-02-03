#include "leetcode/problems/unique-binary-search-trees-ii.h"

namespace leetcode {
namespace problem_95 {

/**
 * @brief 递归生成指定范围内的所有 BST
 * @param start 起始值（包含）
 * @param end 结束值（包含）
 * @return 所有可能的 BST 根节点列表
 */
static vector<TreeNode*> generate(int start, int end) {
  vector<TreeNode*> allTrees;
  
  // 边界条件：范围为空，返回空树
  if (start > end) {
    allTrees.push_back(nullptr);
    return allTrees;
  }
  
  // 枚举每个可能的根节点
  for (int i = start; i <= end; ++i) {
    // 递归生成所有左子树
    vector<TreeNode*> leftTrees = generate(start, i - 1);
    // 递归生成所有右子树
    vector<TreeNode*> rightTrees = generate(i + 1, end);
    
    // 将每棵左子树与每棵右子树组合
    for (TreeNode* left : leftTrees) {
      for (TreeNode* right : rightTrees) {
        TreeNode* root = new TreeNode(i);
        root->left = left;
        root->right = right;
        allTrees.push_back(root);
      }
    }
  }
  
  return allTrees;
}

/**
 * @brief 生成所有由 1~n 组成的唯一 BST
 * 算法：分治递归
 * 时间复杂度：卡特兰数 C(n)，约 4^n / (n^(3/2) * sqrt(pi))
 * 空间复杂度：O(n) 递归栈深度 + 结果存储空间
 */
static vector<TreeNode*> solution1(int n) {
  if (n == 0) {
    return {};
  }
  return generate(1, n);
}

UniqueBinarySearchTreesIiSolution::UniqueBinarySearchTreesIiSolution() {
  setMetaInfo({
    .id = 95,
    .title = "Unique Binary Search Trees II",
    .url = "https://leetcode.com/problems/unique-binary-search-trees-ii/"
  });
  registerStrategy("Divide and Conquer", solution1);
}

vector<TreeNode*> UniqueBinarySearchTreesIiSolution::generateTrees(int n) {
  return getSolution()(n);
}

}  // namespace problem_95
}  // namespace leetcode
