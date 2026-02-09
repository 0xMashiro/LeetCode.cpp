
#include "leetcode/problems/balance-a-binary-search-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1382 {

class BalanceABinarySearchTreeTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BalanceABinarySearchTreeSolution solution;
};

// Example 1: root = [1,null,2,null,3,null,4,null,null]
// 这是一个右偏的链：1->2->3->4
TEST_P(BalanceABinarySearchTreeTest, Example1) {
  // 构建输入树 [1,null,2,null,3,null,4,null,null]
  // 使用 optional 构造: 1, null, 2, null, 3, null, 4
  TreeNode* root = constructTree(vector<optional<int>>{1, nullopt, 2, nullopt, 3, nullopt, 4});
  
  TreeNode* result = solution.balanceBST(root);
  
  // 验证结果是一棵平衡的 BST
  EXPECT_TRUE(isBST(result));
  // 验证中序遍历结果与原树相同（保持节点值）
  EXPECT_EQ(inorderTraversal(root), inorderTraversal(result));
  
  // 清理内存（result 是新树，root 是原树）
  delete root;
  delete result;
}

// Example 2: root = [2,1,3]
// 已经是平衡的
TEST_P(BalanceABinarySearchTreeTest, Example2) {
  TreeNode* root = constructTree(vector<int>{2, 1, 3});
  
  TreeNode* result = solution.balanceBST(root);
  
  // 验证是 BST
  EXPECT_TRUE(isBST(result));
  // 验证中序遍历结果相同
  EXPECT_EQ(inorderTraversal(root), inorderTraversal(result));
  // 已经是平衡树，可以检查是否平衡
  
  delete root;
  delete result;
}

// 边界情况：单节点树
TEST_P(BalanceABinarySearchTreeTest, SingleNode) {
  TreeNode* root = constructTree(vector<int>{1});
  
  TreeNode* result = solution.balanceBST(root);
  
  EXPECT_TRUE(isBST(result));
  EXPECT_EQ(inorderTraversal(root), inorderTraversal(result));
  EXPECT_EQ(1, result->val);
  
  delete root;
  delete result;
}

// 边界情况：左偏树
TEST_P(BalanceABinarySearchTreeTest, LeftSkewedTree) {
  // [4,3,null,2,null,1]
  TreeNode* root = constructTree(vector<optional<int>>{4, 3, nullopt, 2, nullopt, 1});
  
  TreeNode* result = solution.balanceBST(root);
  
  EXPECT_TRUE(isBST(result));
  EXPECT_EQ(inorderTraversal(root), inorderTraversal(result));
  
  delete root;
  delete result;
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BalanceABinarySearchTreeTest,
    ::testing::ValuesIn(BalanceABinarySearchTreeSolution().getStrategyNames()));

}  // namespace problem_1382
}  // namespace leetcode
