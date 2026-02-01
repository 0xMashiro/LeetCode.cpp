
#include "leetcode/problems/longest-zigzag-path-in-a-binary-tree.h"

namespace leetcode {
namespace problem_1372 {

// DFS 解法
// 对于每个节点，计算：
// - leftLen: 从当前节点开始，下一步往左走的最长 ZigZag 路径长度
// - rightLen: 从当前节点开始，下一步往右走的最长 ZigZag 路径长度
// 时间复杂度: O(n)，空间复杂度: O(h) - h为树高度
static int dfs(TreeNode* node, int& result) {
  if (node == nullptr) {
    return 0;
  }
  
  int leftResult = dfs(node->left, result);
  int rightResult = dfs(node->right, result);
  
  // leftLen: 当前节点往左走的最长路径
  // 下一步应该往右，所以使用右子树的 leftResult
  int leftLen = 0;
  // rightLen: 当前节点往右走的最长路径
  // 下一步应该往左，所以使用左子树的 rightResult
  int rightLen = 0;
  
  if (node->left != nullptr) {
    leftLen = 1 + (node->left->right != nullptr ? leftResult : 0);
  }
  if (node->right != nullptr) {
    rightLen = 1 + (node->right->left != nullptr ? rightResult : 0);
  }
  
  // 更新全局最大值
  result = max(result, max(leftLen, rightLen));
  
  // 返回从当前节点开始的两种路径长度信息
  // 但为了简化，我们重新设计返回值
  return 0; // 这个返回值不直接使用
}

// 重新设计的 DFS，返回 pair<leftLen, rightLen>
// leftLen: 从当前节点开始，下一步往左走的最长 ZigZag 长度
// rightLen: 从当前节点开始，下一步往右走的最长 ZigZag 长度
static pair<int, int> dfsPair(TreeNode* node, int& result) {
  if (node == nullptr) {
    return {0, 0};
  }
  
  auto leftPair = dfsPair(node->left, result);
  auto rightPair = dfsPair(node->right, result);
  
  // 从当前节点往左走：长度1 + 左子树的右路径（到左子节点后要往右）
  int leftLen = 0;
  if (node->left != nullptr) {
    leftLen = 1 + leftPair.second;
  }
  
  // 从当前节点往右走：长度1 + 右子树的左路径（到右子节点后要往左）
  int rightLen = 0;
  if (node->right != nullptr) {
    rightLen = 1 + rightPair.first;
  }
  
  // 更新全局最大值
  result = max(result, max(leftLen, rightLen));
  
  return {leftLen, rightLen};
}

static int solution1(TreeNode* root) {
  int result = 0;
  dfsPair(root, result);
  return result;
}

LongestZigzagPathInABinaryTreeSolution::LongestZigzagPathInABinaryTreeSolution() {
  setMetaInfo({
    .id = 1372,
    .title = "Longest ZigZag Path in a Binary Tree",
    .url = "https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/"
  });
  registerStrategy("DFS", solution1);
}

int LongestZigzagPathInABinaryTreeSolution::longestZigZag(TreeNode* root) {
  return getSolution()(root);
}

}  // namespace problem_1372
}  // namespace leetcode
