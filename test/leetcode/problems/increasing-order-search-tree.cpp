#include "leetcode/problems/increasing-order-search-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_897 {

class IncreasingOrderSearchTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  IncreasingOrderSearchTreeSolution solution;
};

TEST_P(IncreasingOrderSearchTreeTest, Example1) {
  // Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
  // Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
  TreeNode* root = constructTree(std::vector<int>{5, 3, 6, 2, 4, -1, 8, 1, -1, -1, -1, 7, 9});
  TreeNode* expected = constructTree(std::vector<int>{1, -1, 2, -1, 3, -1, 4, -1, 5, -1, 6, -1, 7, -1, 8, -1, 9});
  
  TreeNode* result = solution.increasingBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
  
  // 清理内存
  delete root;
  delete result;
  delete expected;
}

TEST_P(IncreasingOrderSearchTreeTest, Example2) {
  // Input: root = [5,1,7]
  // Output: [1,null,5,null,7]
  TreeNode* root = constructTree(std::vector<int>{5, 1, 7});
  TreeNode* expected = constructTree(std::vector<int>{1, -1, 5, -1, 7});
  
  TreeNode* result = solution.increasingBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
  
  // 清理内存
  delete root;
  delete result;
  delete expected;
}

TEST_P(IncreasingOrderSearchTreeTest, SingleNode) {
  // 边界：单节点
  TreeNode* root = constructTree(std::vector<int>{42});
  TreeNode* expected = constructTree(std::vector<int>{42});
  
  TreeNode* result = solution.increasingBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
  
  delete root;
  delete result;
  delete expected;
}

TEST_P(IncreasingOrderSearchTreeTest, LeftSkewedTree) {
  // 边界：左偏树
  // Input: [3,2,null,1]
  // Output: [1,null,2,null,3]
  TreeNode* root = constructTree(std::vector<int>{3, 2, -1, 1});
  TreeNode* expected = constructTree(std::vector<int>{1, -1, 2, -1, 3});
  
  TreeNode* result = solution.increasingBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
  
  delete root;
  delete result;
  delete expected;
}

TEST_P(IncreasingOrderSearchTreeTest, RightSkewedTree) {
  // 边界：右偏树（已经是递增顺序）
  // Input: [1,null,2,null,3]
  // Output: [1,null,2,null,3]
  TreeNode* root = constructTree(std::vector<int>{1, -1, 2, -1, 3});
  TreeNode* expected = constructTree(std::vector<int>{1, -1, 2, -1, 3});
  
  TreeNode* result = solution.increasingBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
  
  delete root;
  delete result;
  delete expected;
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, IncreasingOrderSearchTreeTest,
    ::testing::ValuesIn(IncreasingOrderSearchTreeSolution().getStrategyNames()));

}  // namespace problem_897
}  // namespace leetcode
