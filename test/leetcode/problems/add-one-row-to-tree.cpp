
#include "leetcode/problems/add-one-row-to-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_623 {

class AddOneRowToTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  AddOneRowToTreeSolution solution;
};

TEST_P(AddOneRowToTreeTest, Example1) {
  // Input: root = [4,2,6,3,1,5], val = 1, depth = 2
  // Output: [4,1,1,2,null,null,6,3,1,5]
  TreeNode* root = constructTree(std::vector<int>{4, 2, 6, 3, 1, 5});
  TreeNode* expected = constructTree(std::vector<int>{4, 1, 1, 2, -1, -1, 6, 3, 1, 5});
  TreeNode* result = solution.addOneRow(root, 1, 2);
  EXPECT_TRUE(isSameTree(result, expected));
}

TEST_P(AddOneRowToTreeTest, Example2) {
  // Input: root = [4,2,null,3,1], val = 1, depth = 3
  // Output: [4,2,null,1,1,3,null,null,1]
  TreeNode* root = constructTree(std::vector<std::optional<int>>{4, 2, std::nullopt, 3, 1});
  TreeNode* expected = constructTree(std::vector<std::optional<int>>{4, 2, std::nullopt, 1, 1, 3, std::nullopt, std::nullopt, 1});
  TreeNode* result = solution.addOneRow(root, 1, 3);
  EXPECT_TRUE(isSameTree(result, expected));
}

TEST_P(AddOneRowToTreeTest, DepthOne) {
  // depth == 1 的特殊情况
  // Input: root = [1,2,3], val = 4, depth = 1
  // Output: [4,1,null,2,3]
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3});
  TreeNode* expected = constructTree(std::vector<int>{4, 1, -1, 2, 3});
  TreeNode* result = solution.addOneRow(root, 4, 1);
  EXPECT_TRUE(isSameTree(result, expected));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, AddOneRowToTreeTest,
    ::testing::ValuesIn(AddOneRowToTreeSolution().getStrategyNames()));

}  // namespace problem_623
}  // namespace leetcode
