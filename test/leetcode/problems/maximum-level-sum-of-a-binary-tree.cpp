#include "leetcode/problems/maximum-level-sum-of-a-binary-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1161 {

class MaximumLevelSumOfABinaryTreeTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  MaximumLevelSumOfABinaryTreeSolution solution;
};

TEST_P(MaximumLevelSumOfABinaryTreeTest, Example1) {
  // root = [1,7,0,7,-8,null,null]
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(7);
  root->right = new TreeNode(0);
  root->left->left = new TreeNode(7);
  root->left->right = new TreeNode(-8);
  int expected = 2;
  int result = solution.maxLevelSum(root);
  EXPECT_EQ(expected, result);
  // 不删除节点，避免潜在的双重删除问题
  // 内存泄漏在测试中可接受
}

TEST_P(MaximumLevelSumOfABinaryTreeTest, Example2) {
  // root = [989,null,10250,98693,-89388,null,null,null,-32127]
  TreeNode* root = new TreeNode(989);
  root->right = new TreeNode(10250);
  root->right->left = new TreeNode(98693);
  root->right->right = new TreeNode(-89388);
  root->right->right->right = new TreeNode(-32127);
  int expected = 2;
  int result = solution.maxLevelSum(root);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumLevelSumOfABinaryTreeTest, SingleNode) {
  TreeNode* root = new TreeNode(100);
  int expected = 1;
  int result = solution.maxLevelSum(root);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumLevelSumOfABinaryTreeTest, AllPositive) {
  //       1
  //     2   3
  //    4 5 6 7
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);
  // level1: 1
  // level2: 5
  // level3: 22
  // 最大和是22，层号3
  int expected = 3;
  int result = solution.maxLevelSum(root);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumLevelSumOfABinaryTreeTest, NegativeValues) {
  //       -10
  //      -5  -3
  TreeNode* root = new TreeNode(-10);
  root->left = new TreeNode(-5);
  root->right = new TreeNode(-3);
  // level1: -10
  // level2: -8
  // 最大和是-8，层号2
  int expected = 2;
  int result = solution.maxLevelSum(root);
  EXPECT_EQ(expected, result);
}

TEST_P(MaximumLevelSumOfABinaryTreeTest, TieBreaker) {
  //        1
  //      2   2
  //     3 3 3 3
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(2);
  root->left->left = new TreeNode(3);
  root->left->right = new TreeNode(3);
  root->right->left = new TreeNode(3);
  root->right->right = new TreeNode(3);
  // level1: 1
  // level2: 4
  // level3: 12
  // 最大和是12，层号3
  int expected = 3;
  int result = solution.maxLevelSum(root);
  EXPECT_EQ(expected, result);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, MaximumLevelSumOfABinaryTreeTest,
    ::testing::ValuesIn(MaximumLevelSumOfABinaryTreeSolution().getStrategyNames()));

}  // namespace problem_1161
}  // namespace leetcode