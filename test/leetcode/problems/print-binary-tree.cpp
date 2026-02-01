#include "leetcode/problems/print-binary-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_655 {

class PrintBinaryTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PrintBinaryTreeSolution solution;
};

TEST_P(PrintBinaryTreeTest, Example1) {
  // Input: root = [1,2]
  // Output: [["","1",""],["2","",""]]
  TreeNode* root = constructTree(std::vector<std::optional<int>>{1, 2});
  
  vector<vector<string>> expected = {
    {"", "1", ""},
    {"2", "", ""}
  };
  
  vector<vector<string>> result = solution.printTree(root);
  EXPECT_EQ(expected, result);
  
  // 不需要手动delete，TreeNode有自动析构
}

TEST_P(PrintBinaryTreeTest, Example2) {
  // Input: root = [1,2,3,null,4]
  // Output: [["","","","1","","",""],["","2","","","","3",""],["","","4","","","",""]]
  TreeNode* root = constructTree(std::vector<std::optional<int>>{1, 2, 3, std::nullopt, 4});
  
  vector<vector<string>> expected = {
    {"", "", "", "1", "", "", ""},
    {"", "2", "", "", "", "3", ""},
    {"", "", "4", "", "", "", ""}
  };
  
  vector<vector<string>> result = solution.printTree(root);
  EXPECT_EQ(expected, result);
}

TEST_P(PrintBinaryTreeTest, SingleNode) {
  // 边界: 单节点树
  TreeNode* root = constructTree(std::vector<std::optional<int>>{1});
  
  vector<vector<string>> expected = {{"1"}};
  
  vector<vector<string>> result = solution.printTree(root);
  EXPECT_EQ(expected, result);
}

TEST_P(PrintBinaryTreeTest, CompleteBinaryTree) {
  // 完全二叉树 [1,2,3,4,5,6,7]
  TreeNode* root = constructTree(std::vector<std::optional<int>>{1, 2, 3, 4, 5, 6, 7});
  
  // 高度为2，列数 = 2^3 - 1 = 7
  vector<vector<string>> expected = {
    {"", "", "", "1", "", "", ""},
    {"", "2", "", "", "", "3", ""},
    {"4", "", "5", "", "6", "", "7"}
  };
  
  vector<vector<string>> result = solution.printTree(root);
  EXPECT_EQ(expected, result);
}

TEST_P(PrintBinaryTreeTest, LeftSkewedTree) {
  // 左偏树 [1,2,null,3]
  TreeNode* root = constructTree(std::vector<std::optional<int>>{1, 2, std::nullopt, 3});
  
  vector<vector<string>> result = solution.printTree(root);
  
  // 验证结果：根节点在第0行中间，左子节点在下一行
  EXPECT_EQ(result[0][3], "1");
  EXPECT_EQ(result[1][1], "2");
  EXPECT_EQ(result[2][0], "3");
}

TEST_P(PrintBinaryTreeTest, RightSkewedTree) {
  // 右偏树 [1,null,2,null,3]
  TreeNode* root = constructTree(std::vector<std::optional<int>>{1, std::nullopt, 2, std::nullopt, 3});
  
  vector<vector<string>> result = solution.printTree(root);
  
  // 验证结果
  EXPECT_EQ(result[0][3], "1");
  EXPECT_EQ(result[1][5], "2");
  EXPECT_EQ(result[2][6], "3");
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PrintBinaryTreeTest,
    ::testing::ValuesIn(PrintBinaryTreeSolution().getStrategyNames()));

}  // namespace problem_655
}  // namespace leetcode
