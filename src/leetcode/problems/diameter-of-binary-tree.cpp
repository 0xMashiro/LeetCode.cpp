
#include "leetcode/problems/diameter-of-binary-tree.h"

namespace leetcode {
namespace problem_543 {

// DFS 后序遍历
// 对于每个节点，计算：
// 1. 经过该节点的最长路径 = 左子树深度 + 右子树深度
// 2. 返回该节点的最大深度给父节点
// 时间复杂度: O(n), 空间复杂度: O(h) - h 为树的高度
static int solution1(TreeNode* root) {
  int diameter = 0;
  
  // lambda 函数，计算节点深度并更新直径
  std::function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
    if (node == nullptr) return 0;
    
    int leftDepth = dfs(node->left);
    int rightDepth = dfs(node->right);
    
    // 更新直径：经过当前节点的最长路径
    diameter = max(diameter, leftDepth + rightDepth);
    
    // 返回当前节点的最大深度
    return 1 + max(leftDepth, rightDepth);
  };
  
  dfs(root);
  return diameter;
}

// 不使用 lambda 的写法，使用类成员变量
// 时间复杂度: O(n), 空间复杂度: O(h)
class SolutionHelper {
 public:
  int diameterOfBinaryTree(TreeNode* root) {
    maxDepth(root);
    return diameter;
  }
  
 private:
  int diameter = 0;
  
  int maxDepth(TreeNode* node) {
    if (node == nullptr) return 0;
    
    int leftDepth = maxDepth(node->left);
    int rightDepth = maxDepth(node->right);
    
    diameter = max(diameter, leftDepth + rightDepth);
    
    return 1 + max(leftDepth, rightDepth);
  }
};

static int solution2(TreeNode* root) {
  SolutionHelper helper;
  return helper.diameterOfBinaryTree(root);
}

DiameterOfBinaryTreeSolution::DiameterOfBinaryTreeSolution() {
  setMetaInfo({.id = 543,
               .title = "Diameter of Binary Tree",
               .url = "https://leetcode.com/problems/diameter-of-binary-tree/"});
  registerStrategy("DFS with Lambda", solution1);
  registerStrategy("DFS with Helper Class", solution2);
}

int DiameterOfBinaryTreeSolution::diameterOfBinaryTree(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_543
}  // namespace leetcode
