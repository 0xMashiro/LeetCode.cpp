#include "leetcode/problems/count-complete-tree-nodes.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_222 {

class CountCompleteTreeNodesTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  CountCompleteTreeNodesSolution solution;
};

// Example 1: root = [1,2,3,4,5,6], Output: 6
TEST_P(CountCompleteTreeNodesTest, Example1) {
  std::vector<std::optional<int>> values = {1, 2, 3, 4, 5, 6};
  TreeNode* root = constructTree(values);
  EXPECT_EQ(solution.countNodes(root), 6);
  delete root;
}

// Example 2: root = [], Output: 0
TEST_P(CountCompleteTreeNodesTest, Example2) {
  TreeNode* root = nullptr;
  EXPECT_EQ(solution.countNodes(root), 0);
}

// Example 3: root = [1], Output: 1
TEST_P(CountCompleteTreeNodesTest, Example3) {
  std::vector<std::optional<int>> values = {1};
  TreeNode* root = constructTree(values);
  EXPECT_EQ(solution.countNodes(root), 1);
  delete root;
}

// Additional test: Full binary tree with 3 levels, 7 nodes
TEST_P(CountCompleteTreeNodesTest, FullTree3Levels) {
  std::vector<std::optional<int>> values = {1, 2, 3, 4, 5, 6, 7};
  TreeNode* root = constructTree(values);
  EXPECT_EQ(solution.countNodes(root), 7);
  delete root;
}

// Additional test: Tree with 4 nodes
TEST_P(CountCompleteTreeNodesTest, FourNodes) {
  std::vector<std::optional<int>> values = {1, 2, 3, 4};
  TreeNode* root = constructTree(values);
  EXPECT_EQ(solution.countNodes(root), 4);
  delete root;
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, CountCompleteTreeNodesTest,
    ::testing::ValuesIn(CountCompleteTreeNodesSolution().getStrategyNames()));

}  // namespace problem_222
}  // namespace leetcode
