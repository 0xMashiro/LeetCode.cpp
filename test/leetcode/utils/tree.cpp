#include "leetcode/utils/tree.h"

#include "gtest/gtest.h"

namespace leetcode {
TEST(LeetCodeUtils, TreeConstruct) {
  TreeNode* root1 = new TreeNode(1);
  root1->right = new TreeNode(2);
  root1->right->left = new TreeNode(3);
  std::vector<int> values = {1, -1, 2, 3};
  TreeNode* root2 = constructTree(values);
  EXPECT_EQ(root1->val, root2->val);
  EXPECT_EQ(root1->right->val, root2->right->val);
  EXPECT_EQ(root1->right->left->val, root2->right->left->val);
}

TEST(LeetCodeUtils, TreeConstructOptional) {
  std::vector<std::optional<int>> values = {1, std::nullopt, 2, 3};
  TreeNode* root = constructTree(values);
  EXPECT_EQ(1, root->val);
  EXPECT_EQ(nullptr, root->left);
  EXPECT_EQ(2, root->right->val);
  EXPECT_EQ(3, root->right->left->val);
}

TEST(LeetCodeUtils, TreePreorderTraversal) {
  std::vector<int> values = {1, -1, 2, 3};
  TreeNode* root = constructTree(values);
  std::vector<int> expected = {1, 2, 3};
  std::vector<int> result = preorderTraversal(root);
  EXPECT_EQ(3, result.size());
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, TreeInorderTraversal) {
  std::vector<int> values = {1, -1, 2, 3};
  TreeNode* root = constructTree(values);
  std::vector<int> expected = {1, 3, 2};
  std::vector<int> result = inorderTraversal(root);
  EXPECT_EQ(3, result.size());
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, TreePostorderTraversal) {
  std::vector<int> values = {1, -1, 2, 3};
  TreeNode* root = constructTree(values);
  std::vector<int> expected = {3, 2, 1};
  std::vector<int> result = postorderTraversal(root);
  EXPECT_EQ(3, result.size());
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, TreeLevelOrderTraversal) {
  std::vector<int> values = {3, 9, 20, -1, -1, 15, 7};
  TreeNode* root = constructTree(values);
  std::vector<std::vector<int>> expected = {{3}, {9, 20}, {15, 7}};
  std::vector<std::vector<int>> result = levelOrder(root);
  EXPECT_EQ(3, result.size());
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, TreeInvertTree) {
  std::vector<int> values = {4, 2, 7, 1, 3, 6, 9};
  TreeNode* root = constructTree(values);
  std::vector<int> expected = {4, 7, 2, 9, 6, 3, 1};
  std::vector<int> result = levelOrderTraversal(invertTree(root));
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, IsSameTree) {
  std::vector<int> values1 = {1, 2, 3};
  std::vector<int> values2 = {1, 2, 3};
  TreeNode* root1 = constructTree(values1);
  TreeNode* root2 = constructTree(values2);
  EXPECT_TRUE(isSameTree(root1, root2));
}
}  // namespace leetcode