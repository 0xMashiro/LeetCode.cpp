#include "leetcode/problems/convert-bst-to-greater-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_538 {

class ConvertBstToGreaterTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ConvertBstToGreaterTreeSolution solution;
};

// 示例1: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
// 输出: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
TEST_P(ConvertBstToGreaterTreeTest, Example1) {
  // 构建输入树: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
  // 使用-1表示null
  std::vector<int> input1 = {4, 1, 6, 0, 2, 5, 7, -1, -1, -1, 3, -1, -1, -1, 8};
  TreeNode* root = constructTree(input1);
  
  // 构建期望输出树: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
  std::vector<int> expect1 = {30, 36, 21, 36, 35, 26, 15, -1, -1, -1, 33, -1, -1, -1, 8};
  TreeNode* expected = constructTree(expect1);
  
  TreeNode* result = solution.convertBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
  
  // 不需要手动delete，TreeNode有自动析构
}

// 示例2: root = [0,null,1]
// 输出: [1,null,1]
TEST_P(ConvertBstToGreaterTreeTest, Example2) {
  // 构建输入树: [0,null,1]
  std::vector<int> input2 = {0, -1, 1};
  TreeNode* root = constructTree(input2);
  
  // 构建期望输出树: [1,null,1]
  std::vector<int> expect2 = {1, -1, 1};
  TreeNode* expected = constructTree(expect2);
  
  TreeNode* result = solution.convertBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
}

// 边界情况: 空树
TEST_P(ConvertBstToGreaterTreeTest, EmptyTree) {
  TreeNode* root = nullptr;
  TreeNode* result = solution.convertBST(root);
  EXPECT_EQ(result, nullptr);
}

// 边界情况: 单节点树
TEST_P(ConvertBstToGreaterTreeTest, SingleNode) {
  std::vector<int> input4 = {5};
  TreeNode* root = constructTree(input4);
  std::vector<int> expect4 = {5};  // 只有一个节点，累加和就是它自己
  TreeNode* expected = constructTree(expect4);
  
  TreeNode* result = solution.convertBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
}

// 边界情况: 只有两个节点（根和右子节点）
TEST_P(ConvertBstToGreaterTreeTest, TwoNodes) {
  // 输入: [1,-1,2]，根=1，右子节点=2
  std::vector<int> input5 = {1, -1, 2};
  TreeNode* root = constructTree(input5);
  // 期望: [3,-1,2]，根=1+2=3，右子节点=2（没有比2更大的）
  std::vector<int> expect5 = {3, -1, 2};
  TreeNode* expected = constructTree(expect5);
  
  TreeNode* result = solution.convertBST(root);
  
  EXPECT_TRUE(isSameTree(result, expected));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ConvertBstToGreaterTreeTest,
    ::testing::ValuesIn(ConvertBstToGreaterTreeSolution().getStrategyNames()));

}  // namespace problem_538
}  // namespace leetcode
