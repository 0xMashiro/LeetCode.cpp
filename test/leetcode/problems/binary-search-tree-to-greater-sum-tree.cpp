#include "leetcode/problems/binary-search-tree-to-greater-sum-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1038 {

using std::nullopt;
using std::optional;
using std::vector;

class BinarySearchTreeToGreaterSumTreeTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BinarySearchTreeToGreaterSumTreeSolution solution;
};

TEST_P(BinarySearchTreeToGreaterSumTreeTest, Example1) {
  // Input: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
  // Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
  vector<optional<int>> input = {4, 1, 6, 0, 2, 5, 7, nullopt, nullopt, nullopt, 3, nullopt, nullopt, nullopt, 8};
  vector<optional<int>> expected = {30, 36, 21, 36, 35, 26, 15, nullopt, nullopt, nullopt, 33, nullopt, nullopt, nullopt, 8};
  
  TreeNode* root = constructTree(input);
  TreeNode* expectedTree = constructTree(expected);
  
  TreeNode* result = solution.bstToGst(root);
  
  EXPECT_TRUE(isSameTree(result, expectedTree));
  // Trees are automatically destructed
}

TEST_P(BinarySearchTreeToGreaterSumTreeTest, Example2) {
  // Input: [0,null,1]
  // Output: [1,null,1]
  // Explanation: 
  // - Node 1 (right): no greater nodes, sum=0+1=1, new val=1
  // - Node 0 (root): greater nodes=[1], sum=1+0=1, new val=1
  vector<optional<int>> input = {0, nullopt, 1};
  vector<optional<int>> expected = {1, nullopt, 1};
  
  TreeNode* root = constructTree(input);
  TreeNode* expectedTree = constructTree(expected);
  
  TreeNode* result = solution.bstToGst(root);
  
  EXPECT_TRUE(isSameTree(result, expectedTree));
}

TEST_P(BinarySearchTreeToGreaterSumTreeTest, SingleNode) {
  // Single node tree: [5]
  // No greater nodes, value stays 5
  vector<optional<int>> input = {5};
  vector<optional<int>> expected = {5};
  
  TreeNode* root = constructTree(input);
  TreeNode* expectedTree = constructTree(expected);
  
  TreeNode* result = solution.bstToGst(root);
  
  EXPECT_TRUE(isSameTree(result, expectedTree));
}

TEST_P(BinarySearchTreeToGreaterSumTreeTest, RightSkewedTree) {
  // Right skewed tree: 1 -> 2 -> 3
  // Input: [1, null, 2, null, 3]
  // Reverse inorder: 3, 2, 1
  // - Node 3: sum=3, new val=3
  // - Node 2: sum=3+2=5, new val=5
  // - Node 1: sum=5+1=6, new val=6
  // Expected: [6, null, 5, null, 3]
  vector<optional<int>> input = {1, nullopt, 2, nullopt, 3};
  vector<optional<int>> expected = {6, nullopt, 5, nullopt, 3};
  
  TreeNode* root = constructTree(input);
  TreeNode* expectedTree = constructTree(expected);
  
  TreeNode* result = solution.bstToGst(root);
  
  EXPECT_TRUE(isSameTree(result, expectedTree));
}

TEST_P(BinarySearchTreeToGreaterSumTreeTest, LeftSkewedTree) {
  // Left skewed tree: 3 -> 2 -> 1
  // Input: [3, 2, null, 1]
  // Tree structure:
  //     3
  //    /
  //   2
  //  /
  // 1
  // Reverse inorder: 3, 2, 1
  // - Node 3: sum=3, new val=3
  // - Node 2: sum=3+2=5, new val=5
  // - Node 1: sum=5+1=6, new val=6
  // Expected: [3, 5, null, 6]
  vector<optional<int>> input = {3, 2, nullopt, 1};
  vector<optional<int>> expected = {3, 5, nullopt, 6};
  
  TreeNode* root = constructTree(input);
  TreeNode* expectedTree = constructTree(expected);
  
  TreeNode* result = solution.bstToGst(root);
  
  EXPECT_TRUE(isSameTree(result, expectedTree));
}

TEST_P(BinarySearchTreeToGreaterSumTreeTest, TwoNodes) {
  // Two nodes: root=2, left=1
  // Input: [2, 1]
  // Tree structure:
  //   2
  //  /
  // 1
  // Reverse inorder: 2, 1
  // - Node 2: sum=2, new val=2
  // - Node 1: sum=2+1=3, new val=3
  // Expected: [2, 3]
  vector<optional<int>> input = {2, 1};
  vector<optional<int>> expected = {2, 3};
  
  TreeNode* root = constructTree(input);
  TreeNode* expectedTree = constructTree(expected);
  
  TreeNode* result = solution.bstToGst(root);
  
  EXPECT_TRUE(isSameTree(result, expectedTree));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BinarySearchTreeToGreaterSumTreeTest,
    ::testing::ValuesIn(BinarySearchTreeToGreaterSumTreeSolution().getStrategyNames()));

}  // namespace problem_1038
}  // namespace leetcode
