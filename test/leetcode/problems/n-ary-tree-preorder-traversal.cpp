#include "leetcode/problems/n-ary-tree-preorder-traversal.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_589 {

class NAryTreePreorderTraversalTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NAryTreePreorderTraversalSolution solution;
};

TEST_P(NAryTreePreorderTraversalTest, Example1) {
  // Input: root = [1,null,3,2,4,null,5,6]
  // Output: [1,3,5,6,2,4]
  vector<optional<int>> values = {1, nullopt, 3, 2, 4, nullopt, 5, 6};
  Node* root = constructNaryTree(values);
  vector<int> expected = {1, 3, 5, 6, 2, 4};
  EXPECT_EQ(expected, solution.preorder(root));
  delete root;
}

TEST_P(NAryTreePreorderTraversalTest, Example2) {
  // Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
  // Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
  vector<optional<int>> values = {1,    nullopt, 2,    3,    4,    5,    nullopt,
                                   nullopt, 6,    7,    nullopt, 8,    nullopt,
                                   9,    10,   nullopt, nullopt, 11,   nullopt,
                                   12,   nullopt, 13,   nullopt, nullopt, 14};
  Node* root = constructNaryTree(values);
  vector<int> expected = {1, 2, 3, 6, 7, 11, 14, 4, 8, 12, 5, 9, 13, 10};
  EXPECT_EQ(expected, solution.preorder(root));
  delete root;
}

TEST_P(NAryTreePreorderTraversalTest, EmptyTree) {
  // Input: root = []
  // Output: []
  Node* root = nullptr;
  vector<int> expected = {};
  EXPECT_EQ(expected, solution.preorder(root));
}

TEST_P(NAryTreePreorderTraversalTest, SingleNode) {
  // Input: root = [1]
  // Output: [1]
  vector<optional<int>> values = {1};
  Node* root = constructNaryTree(values);
  vector<int> expected = {1};
  EXPECT_EQ(expected, solution.preorder(root));
  delete root;
}

TEST_P(NAryTreePreorderTraversalTest, OnlyRootWithChildren) {
  // Input: root = [1,null,2,3,4]
  // Output: [1,2,3,4]
  vector<optional<int>> values = {1, nullopt, 2, 3, 4};
  Node* root = constructNaryTree(values);
  vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(expected, solution.preorder(root));
  delete root;
}

TEST_P(NAryTreePreorderTraversalTest, LinearChain) {
  // Each node has only one child
  // Input: root = [1,null,2,null,3,null,4]
  // Output: [1,2,3,4]
  vector<optional<int>> values = {1, nullopt, 2, nullopt, 3, nullopt, 4};
  Node* root = constructNaryTree(values);
  vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(expected, solution.preorder(root));
  delete root;
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NAryTreePreorderTraversalTest,
    ::testing::ValuesIn(NAryTreePreorderTraversalSolution().getStrategyNames()));

}  // namespace problem_589
}  // namespace leetcode
