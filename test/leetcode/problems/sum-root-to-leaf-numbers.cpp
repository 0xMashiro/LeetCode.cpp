#include "leetcode/problems/sum-root-to-leaf-numbers.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_129 {

class SumRootToLeafNumbersTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SumRootToLeafNumbersSolution solution;
};

// Example 1: root = [1,2,3], output = 25
// Paths: 1->2 = 12, 1->3 = 13, sum = 25
TEST_P(SumRootToLeafNumbersTest, Example1) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3});
  EXPECT_EQ(solution.sumNumbers(root), 25);
}

// Example 2: root = [4,9,0,5,1], output = 1026
// Paths: 4->9->5 = 495, 4->9->1 = 491, 4->0 = 40, sum = 1026
TEST_P(SumRootToLeafNumbersTest, Example2) {
  TreeNode* root = constructTree(std::vector<int>{4, 9, 0, 5, 1});
  EXPECT_EQ(solution.sumNumbers(root), 1026);
}

// 边界情况：单节点树
TEST_P(SumRootToLeafNumbersTest, SingleNode) {
  TreeNode* root = constructTree(std::vector<int>{5});
  EXPECT_EQ(solution.sumNumbers(root), 5);
}

// 边界情况：只有左子树 (1->2->3 = 123)
TEST_P(SumRootToLeafNumbersTest, LeftOnlyTree) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, -1, 3});
  EXPECT_EQ(solution.sumNumbers(root), 123);
}

// 边界情况：包含 0 的路径 (1->0 = 10, 1->0 = 10, sum = 20)
TEST_P(SumRootToLeafNumbersTest, PathWithZero) {
  TreeNode* root = constructTree(std::vector<int>{1, 0, 0});
  EXPECT_EQ(solution.sumNumbers(root), 20);
}

// 边界情况：完全二叉树，多个叶子
// Paths: 1->2->4 = 124, 1->2->5 = 125, 1->3->6 = 136, 1->3->7 = 137, sum = 522
TEST_P(SumRootToLeafNumbersTest, FullBinaryTree) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3, 4, 5, 6, 7});
  EXPECT_EQ(solution.sumNumbers(root), 522);
}

// 边界情况：所有节点值为 0
TEST_P(SumRootToLeafNumbersTest, AllZeros) {
  TreeNode* root = constructTree(std::vector<int>{0, 0, 0});
  EXPECT_EQ(solution.sumNumbers(root), 0);
}

// 边界情况：空树（虽然题目说节点数>=1，但测试一下鲁棒性）
TEST_P(SumRootToLeafNumbersTest, EmptyTree) {
  TreeNode* root = nullptr;
  EXPECT_EQ(solution.sumNumbers(root), 0);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SumRootToLeafNumbersTest,
    ::testing::ValuesIn(SumRootToLeafNumbersSolution().getStrategyNames()));

}  // namespace problem_129
}  // namespace leetcode
