#include "leetcode/problems/delete-leaves-with-a-given-value.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1325 {

class DeleteLeavesWithAGivenValueTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  DeleteLeavesWithAGivenValueSolution solution;
};

//! Example 1: root = [1,2,3,2,null,2,4], target = 2
//! Output: [1,null,3,null,4]
//! Explanation: Leaf nodes with value 2 are removed.
//! After removing, new nodes become leaf nodes with value 2 are also removed.
TEST_P(DeleteLeavesWithAGivenValueTest, Example1) {
  // 构建输入树: [1,2,3,2,null,2,4]
  //        1
  //       / \
  //      2   3
  //     /   / \
  //    2   2   4
  auto root = constructTree(std::vector<std::optional<int>>{1, 2, 3, 2, std::nullopt, 2, 4});
  int target = 2;
  
  auto result = solution.removeLeafNodes(root, target);
  
  // 期望结果: [1,null,3,null,4]
  //        1
  //         \
  //          3
  //           \
  //            4
  auto expected = constructTree(std::vector<std::optional<int>>{1, std::nullopt, 3, std::nullopt, 4});
  
  EXPECT_TRUE(isSameTree(result, expected));
  // 注意：不要手动 delete，TreeNode 会自动处理内存释放
}

//! Example 2: root = [1,3,3,3,2], target = 3
//! Output: [1,3,null,null,2]
TEST_P(DeleteLeavesWithAGivenValueTest, Example2) {
  // 构建输入树: [1,3,3,3,2]
  //        1
  //       / \
  //      3   3
  //     / \
  //    3   2
  auto root = constructTree(std::vector<std::optional<int>>{1, 3, 3, 3, 2});
  int target = 3;
  
  auto result = solution.removeLeafNodes(root, target);
  
  // 期望结果: [1,3,null,null,2]
  //        1
  //       / \
  //      3   2
  auto expected = constructTree(std::vector<std::optional<int>>{1, 3, std::nullopt, std::nullopt, 2});
  
  EXPECT_TRUE(isSameTree(result, expected));
}

//! Example 3: root = [1,2,null,2,null,2], target = 2
//! Output: [1]
TEST_P(DeleteLeavesWithAGivenValueTest, Example3) {
  // 构建输入树: [1,2,null,2,null,2]
  //        1
  //       /
  //      2
  //     /
  //    2
  //   /
  //  2
  auto root = constructTree(std::vector<std::optional<int>>{1, 2, std::nullopt, 2, std::nullopt, 2});
  int target = 2;
  
  auto result = solution.removeLeafNodes(root, target);
  
  // 期望结果: [1]
  auto expected = constructTree(std::vector<std::optional<int>>{1});
  
  EXPECT_TRUE(isSameTree(result, expected));
}

//! 边界测试：空树
TEST_P(DeleteLeavesWithAGivenValueTest, EmptyTree) {
  TreeNode* root = nullptr;
  int target = 1;
  
  auto result = solution.removeLeafNodes(root, target);
  
  EXPECT_EQ(result, nullptr);
}

//! 边界测试：单节点，值等于 target
TEST_P(DeleteLeavesWithAGivenValueTest, SingleNodeTarget) {
  auto root = constructTree(std::vector<std::optional<int>>{1});
  int target = 1;
  
  auto result = solution.removeLeafNodes(root, target);
  
  EXPECT_EQ(result, nullptr);
}

//! 边界测试：单节点，值不等于 target
TEST_P(DeleteLeavesWithAGivenValueTest, SingleNodeNotTarget) {
  auto root = constructTree(std::vector<std::optional<int>>{1});
  int target = 2;
  
  auto result = solution.removeLeafNodes(root, target);
  
  auto expected = constructTree(std::vector<std::optional<int>>{1});
  EXPECT_TRUE(isSameTree(result, expected));
}

//! 边界测试：所有节点都需要删除
TEST_P(DeleteLeavesWithAGivenValueTest, AllNodesRemoved) {
  // 树: [1,1,1,1,1,1,1], target = 1
  // 所有节点的值都是 1，最终会全部删除
  auto root = constructTree(std::vector<std::optional<int>>{1, 1, 1, 1, 1, 1, 1});
  int target = 1;
  
  auto result = solution.removeLeafNodes(root, target);
  
  EXPECT_EQ(result, nullptr);
}

//! 边界测试：没有节点需要删除
TEST_P(DeleteLeavesWithAGivenValueTest, NoNodesRemoved) {
  // 树: [1,2,3,4,5], target = 6
  auto root = constructTree(std::vector<std::optional<int>>{1, 2, 3, 4, 5});
  int target = 6;
  
  auto result = solution.removeLeafNodes(root, target);
  
  auto expected = constructTree(std::vector<std::optional<int>>{1, 2, 3, 4, 5});
  EXPECT_TRUE(isSameTree(result, expected));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, DeleteLeavesWithAGivenValueTest,
    ::testing::ValuesIn(DeleteLeavesWithAGivenValueSolution().getStrategyNames()));

}  // namespace problem_1325
}  // namespace leetcode
