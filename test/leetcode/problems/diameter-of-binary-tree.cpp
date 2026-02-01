
#include "leetcode/problems/diameter-of-binary-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_543 {

class DiameterOfBinaryTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DiameterOfBinaryTreeSolution solution;
};

// Example 1: root = [1,2,3,4,5], output = 3
// 解释: 路径 [4,2,1,3] 或 [5,2,1,3] 的长度为 3 条边
TEST_P(DiameterOfBinaryTreeTest, Example1) {
  // 构建树 [1,2,3,4,5]
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  
  EXPECT_EQ(3, solution.diameterOfBinaryTree(root));
  
  delete root;  // 自动删除所有子节点
}

// Example 2: root = [1,2], output = 1
TEST_P(DiameterOfBinaryTreeTest, Example2) {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  
  EXPECT_EQ(1, solution.diameterOfBinaryTree(root));
  
  delete root;
}

// 边界情况：单节点，输出 0
TEST_P(DiameterOfBinaryTreeTest, SingleNode) {
  TreeNode* root = new TreeNode(1);
  
  EXPECT_EQ(0, solution.diameterOfBinaryTree(root));
  
  delete root;
}

// 边界情况：链状树（完全左偏）
// root = [1,2,null,3,null,4], 最长路径为 3
TEST_P(DiameterOfBinaryTreeTest, LeftChain) {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->left->left = new TreeNode(3);
  root->left->left->left = new TreeNode(4);
  
  EXPECT_EQ(3, solution.diameterOfBinaryTree(root));
  
  delete root;
}

// 边界情况：链状树（完全右偏）
TEST_P(DiameterOfBinaryTreeTest, RightChain) {
  TreeNode* root = new TreeNode(1);
  root->right = new TreeNode(2);
  root->right->right = new TreeNode(3);
  root->right->right->right = new TreeNode(4);
  
  EXPECT_EQ(3, solution.diameterOfBinaryTree(root));
  
  delete root;
}

// 复杂树：直径不经过根节点
//       1
//      /
//     2
//    / \
//   3   4
//  /     \
// 5       6
// 直径应该是 5-3-2-4-6，长度为 4
TEST_P(DiameterOfBinaryTreeTest, DiameterNotThroughRoot) {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->left->left = new TreeNode(3);
  root->left->right = new TreeNode(4);
  root->left->left->left = new TreeNode(5);
  root->left->right->right = new TreeNode(6);
  
  EXPECT_EQ(4, solution.diameterOfBinaryTree(root));
  
  delete root;
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DiameterOfBinaryTreeTest,
    ::testing::ValuesIn(DiameterOfBinaryTreeSolution().getStrategyNames()));

}  // namespace problem_543
}  // namespace leetcode
