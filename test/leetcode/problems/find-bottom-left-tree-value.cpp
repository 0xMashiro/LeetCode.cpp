#include "leetcode/problems/find-bottom-left-tree-value.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_513 {

class FindBottomLeftTreeValueTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  FindBottomLeftTreeValueSolution solution;
};

// 示例1: root = [2,1,3], 输出: 1
TEST_P(FindBottomLeftTreeValueTest, Example1) {
  TreeNode* root = constructTree(std::vector<int>{2, 1, 3});
  EXPECT_EQ(solution.findBottomLeftValue(root), 1);
  // root 会自动析构，无需手动 delete
}

// 示例2: root = [1,2,3,4,null,5,6,null,null,7], 输出: 7
TEST_P(FindBottomLeftTreeValueTest, Example2) {
  // 使用 optional 版本构造，null 节点用 std::nullopt 表示
  TreeNode* root = constructTree(std::vector<std::optional<int>>{
      1, 2, 3, 4, std::nullopt, 5, 6, std::nullopt, std::nullopt, 7});
  EXPECT_EQ(solution.findBottomLeftValue(root), 7);
}

// 边界：单节点树
TEST_P(FindBottomLeftTreeValueTest, SingleNode) {
  TreeNode* root = constructTree(std::vector<int>{42});
  EXPECT_EQ(solution.findBottomLeftValue(root), 42);
}

// 边界：只有左子树的树
TEST_P(FindBottomLeftTreeValueTest, LeftSkewedTree) {
  // 树: 1 -> 2 -> 3 -> 4 (全是左子树)
  TreeNode* root = constructTree(std::vector<int>{1, 2, -1, 3, -1, 4, -1});
  EXPECT_EQ(solution.findBottomLeftValue(root), 4);
}

// 边界：只有右子树的树
TEST_P(FindBottomLeftTreeValueTest, RightSkewedTree) {
  // 树: 1 -> 2 -> 3 -> 4 (全是右子树)
  TreeNode* root = constructTree(std::vector<int>{1, -1, 2, -1, 3, -1, 4});
  EXPECT_EQ(solution.findBottomLeftValue(root), 4);
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, FindBottomLeftTreeValueTest,
    ::testing::ValuesIn(FindBottomLeftTreeValueSolution().getStrategyNames()));

}  // namespace problem_513
}  // namespace leetcode
