#include "leetcode/problems/construct-binary-tree-from-inorder-and-postorder-traversal.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_106 {

class ConstructBinaryTreeFromInorderAndPostorderTraversalTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConstructBinaryTreeFromInorderAndPostorderTraversalSolution solution;
};

TEST_P(ConstructBinaryTreeFromInorderAndPostorderTraversalTest, Example1) {
  // Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
  // Output: [3,9,20,null,null,15,7]
  vector<int> inorder = {9, 3, 15, 20, 7};
  vector<int> postorder = {9, 15, 7, 20, 3};
  
  TreeNode* result = solution.buildTree(inorder, postorder);
  
  // 验证构建的树是正确的
  // 通过比较中序和后序遍历结果
  EXPECT_EQ(inorder, inorderTraversal(result));
  EXPECT_EQ(postorder, postorderTraversal(result));
  
  // 也可以直接构造期望的树进行比较
  TreeNode* expected = constructTree(std::vector<int>{3, 9, 20, -1, -1, 15, 7});
  EXPECT_TRUE(isSameTree(result, expected));
}

TEST_P(ConstructBinaryTreeFromInorderAndPostorderTraversalTest, Example2) {
  // Input: inorder = [-1], postorder = [-1]
  // Output: [-1]
  vector<int> inorder = {-1};
  vector<int> postorder = {-1};
  
  TreeNode* result = solution.buildTree(inorder, postorder);
  
  EXPECT_EQ(inorder, inorderTraversal(result));
  EXPECT_EQ(postorder, postorderTraversal(result));
  
  TreeNode* expected = constructTree(std::vector<int>{-1});
  EXPECT_TRUE(isSameTree(result, expected));
}

TEST_P(ConstructBinaryTreeFromInorderAndPostorderTraversalTest, EmptyTree) {
  // 空树的情况
  vector<int> inorder = {};
  vector<int> postorder = {};
  
  TreeNode* result = solution.buildTree(inorder, postorder);
  
  EXPECT_EQ(nullptr, result);
}

TEST_P(ConstructBinaryTreeFromInorderAndPostorderTraversalTest, LeftSkewedTree) {
  // 左斜树：1->2->3 (每个节点只有左孩子)
  // 中序: [3,2,1], 后序: [3,2,1]
  vector<int> inorder = {3, 2, 1};
  vector<int> postorder = {3, 2, 1};
  
  TreeNode* result = solution.buildTree(inorder, postorder);
  
  EXPECT_EQ(inorder, inorderTraversal(result));
  EXPECT_EQ(postorder, postorderTraversal(result));
}

TEST_P(ConstructBinaryTreeFromInorderAndPostorderTraversalTest, RightSkewedTree) {
  // 右斜树：1->2->3 (每个节点只有右孩子)
  // 中序: [1,2,3], 后序: [3,2,1]
  vector<int> inorder = {1, 2, 3};
  vector<int> postorder = {3, 2, 1};
  
  TreeNode* result = solution.buildTree(inorder, postorder);
  
  EXPECT_EQ(inorder, inorderTraversal(result));
  EXPECT_EQ(postorder, postorderTraversal(result));
}

TEST_P(ConstructBinaryTreeFromInorderAndPostorderTraversalTest, CompleteBinaryTree) {
  // 完全二叉树
  //       1
  //     /   \
  //    2     3
  //   / \   /
  //  4   5 6
  // 中序: [4,2,5,1,6,3]
  // 后序: [4,5,2,6,3,1]
  vector<int> inorder = {4, 2, 5, 1, 6, 3};
  vector<int> postorder = {4, 5, 2, 6, 3, 1};
  
  TreeNode* result = solution.buildTree(inorder, postorder);
  
  EXPECT_EQ(inorder, inorderTraversal(result));
  EXPECT_EQ(postorder, postorderTraversal(result));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConstructBinaryTreeFromInorderAndPostorderTraversalTest,
    ::testing::ValuesIn(ConstructBinaryTreeFromInorderAndPostorderTraversalSolution().getStrategyNames()));

}  // namespace problem_106
}  // namespace leetcode
