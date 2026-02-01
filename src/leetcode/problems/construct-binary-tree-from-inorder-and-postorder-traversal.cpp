#include "leetcode/problems/construct-binary-tree-from-inorder-and-postorder-traversal.h"

namespace leetcode {
namespace problem_106 {

/**
 * 递归构建二叉树
 * 思路：
 * 1. 后序遍历的最后一个元素是根节点
 * 2. 在中序遍历中找到根节点，左边是左子树，右边是右子树
 * 3. 递归构建左右子树
 * 
 * 时间复杂度: O(n)，每个节点只被访问一次
 * 空间复杂度: O(n)，哈希表存储中序索引 + 递归栈
 */
class Solution {
 public:
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int n = inorder.size();
    // 建立中序值到索引的映射，用于 O(1) 查找
    for (int i = 0; i < n; ++i) {
      index_map_[inorder[i]] = i;
    }
    return build(inorder, postorder, 0, n - 1, 0, n - 1);
  }

 private:
  unordered_map<int, int> index_map_;

  TreeNode* build(vector<int>& inorder, vector<int>& postorder,
                  int in_left, int in_right,
                  int post_left, int post_right) {
    // 递归终止条件
    if (in_left > in_right || post_left > post_right) {
      return nullptr;
    }

    // 后序遍历的最后一个元素是根节点
    int root_val = postorder[post_right];
    TreeNode* root = new TreeNode(root_val);

    // 在中序遍历中找到根节点的位置
    int in_root_idx = index_map_[root_val];
    // 左子树的节点数
    int left_size = in_root_idx - in_left;

    // 递归构建左子树
    // 中序：in_left 到 in_root_idx - 1
    // 后序：post_left 到 post_left + left_size - 1
    root->left = build(inorder, postorder, 
                       in_left, in_root_idx - 1,
                       post_left, post_left + left_size - 1);

    // 递归构建右子树
    // 中序：in_root_idx + 1 到 in_right
    // 后序：post_left + left_size 到 post_right - 1
    root->right = build(inorder, postorder,
                        in_root_idx + 1, in_right,
                        post_left + left_size, post_right - 1);

    return root;
  }
};

static TreeNode* solution1(vector<int>& inorder, vector<int>& postorder) {
  Solution sol;
  return sol.buildTree(inorder, postorder);
}

ConstructBinaryTreeFromInorderAndPostorderTraversalSolution::ConstructBinaryTreeFromInorderAndPostorderTraversalSolution() {
  setMetaInfo({.id = 106,
               .title = "Construct Binary Tree from Inorder and Postorder Traversal",
               .url = "https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/"});
  registerStrategy("Recursive with HashMap", solution1);
}

TreeNode* ConstructBinaryTreeFromInorderAndPostorderTraversalSolution::buildTree(vector<int>& inorder, vector<int>& postorder) {
  return getSolution()(inorder, postorder);
}

}  // namespace problem_106
}  // namespace leetcode
