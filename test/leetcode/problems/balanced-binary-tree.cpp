
#include "leetcode/problems/balanced-binary-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_110 {

class BalancedBinaryTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  BalancedBinaryTreeSolution solution;
};

// Example 1: root = [3,9,20,null,null,15,7] -> true
TEST_P(BalancedBinaryTreeTest, Example1) {
  std::vector<std::optional<int>> values = {3, 9, 20, std::nullopt, std::nullopt, 15, 7};
  TreeNode* root = constructTree(values);
  EXPECT_TRUE(solution.isBalanced(root));
}

// Example 2: root = [1,2,2,3,3,null,null,4,4] -> false
TEST_P(BalancedBinaryTreeTest, Example2) {
  std::vector<std::optional<int>> values = {1, 2, 2, 3, 3, std::nullopt, std::nullopt, 4, 4};
  TreeNode* root = constructTree(values);
  EXPECT_FALSE(solution.isBalanced(root));
}

// Example 3: root = [] -> true
TEST_P(BalancedBinaryTreeTest, Example3) {
  TreeNode* root = nullptr;
  EXPECT_TRUE(solution.isBalanced(root));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, BalancedBinaryTreeTest,
    ::testing::ValuesIn(BalancedBinaryTreeSolution().getStrategyNames()));

}  // namespace problem_110
}  // namespace leetcode
