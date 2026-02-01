#include "leetcode/problems/delete-leaves-with-a-given-value.h"

namespace leetcode {
namespace problem_1325 {

/**
 * 后序遍历递归删除叶子节点
 * 思路：
 * 1. 先递归处理左右子树（后序遍历）
 * 2. 处理完子树后，检查当前节点是否变成叶子节点
 * 3. 如果当前节点是叶子节点且值等于 target，则删除该节点（返回 nullptr）
 * 4. 否则返回当前节点
 * 
 * 时间复杂度：O(n)，每个节点只访问一次
 * 空间复杂度：O(h)，递归栈深度，h 为树的高度
 */
static TreeNode* solution1(TreeNode* root, int target) {
  if (root == nullptr) {
    return nullptr;
  }
  
  // 后序遍历：先处理左右子树
  root->left = solution1(root->left, target);
  root->right = solution1(root->right, target);
  
  // 检查当前节点是否是叶子节点且值为 target
  if (root->left == nullptr && root->right == nullptr && root->val == target) {
    // 返回 nullptr 表示删除该节点
    // TreeNode 会自动处理内存释放（析构时会递归删除子节点）
    return nullptr;
  }
  
  return root;
}

DeleteLeavesWithAGivenValueSolution::DeleteLeavesWithAGivenValueSolution() {
  setMetaInfo({.id = 1325,
               .title = "Delete Leaves With a Given Value",
               .url = "https://leetcode.com/problems/delete-leaves-with-a-given-value/"});
  registerStrategy("Postorder DFS", solution1);
}

TreeNode* DeleteLeavesWithAGivenValueSolution::removeLeafNodes(TreeNode* root, int target) {
  return getSolution()(root, target);
}

}  // namespace problem_1325
}  // namespace leetcode
