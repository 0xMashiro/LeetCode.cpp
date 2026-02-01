#include "leetcode/problems/vertical-order-traversal-of-a-binary-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_987 {

class VerticalOrderTraversalOfABinaryTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  VerticalOrderTraversalOfABinaryTreeSolution solution;
};

TEST_P(VerticalOrderTraversalOfABinaryTreeTest, Example1) {
  // Input: root = [3,9,20,null,null,15,7]
  // Output: [[9],[3,15],[20],[7]]
  std::vector<int> values = {3, 9, 20, -1, -1, 15, 7};
  TreeNode* root = constructTree(values);
  vector<vector<int>> expected = {{9}, {3, 15}, {20}, {7}};
  EXPECT_EQ(expected, solution.verticalTraversal(root));
}

TEST_P(VerticalOrderTraversalOfABinaryTreeTest, Example2) {
  // Input: root = [1,2,3,4,5,6,7]
  // Output: [[4],[2],[1,5,6],[3],[7]]
  std::vector<int> values = {1, 2, 3, 4, 5, 6, 7};
  TreeNode* root = constructTree(values);
  vector<vector<int>> expected = {{4}, {2}, {1, 5, 6}, {3}, {7}};
  EXPECT_EQ(expected, solution.verticalTraversal(root));
}

TEST_P(VerticalOrderTraversalOfABinaryTreeTest, Example3) {
  // Input: root = [1,2,3,4,6,5,7]
  // Output: [[4],[2],[1,5,6],[3],[7]]
  std::vector<int> values = {1, 2, 3, 4, 6, 5, 7};
  TreeNode* root = constructTree(values);
  vector<vector<int>> expected = {{4}, {2}, {1, 5, 6}, {3}, {7}};
  EXPECT_EQ(expected, solution.verticalTraversal(root));
}

TEST_P(VerticalOrderTraversalOfABinaryTreeTest, SingleNode) {
  // 边界：单节点
  std::vector<int> values = {1};
  TreeNode* root = constructTree(values);
  vector<vector<int>> expected = {{1}};
  EXPECT_EQ(expected, solution.verticalTraversal(root));
}

TEST_P(VerticalOrderTraversalOfABinaryTreeTest, LeftSkewedTree) {
  // 边界：左斜树
  std::vector<int> values = {1, 2, -1, 3, -1};
  TreeNode* root = constructTree(values);
  vector<vector<int>> expected = {{3}, {2}, {1}};
  EXPECT_EQ(expected, solution.verticalTraversal(root));
}

TEST_P(VerticalOrderTraversalOfABinaryTreeTest, RightSkewedTree) {
  // 边界：右斜树
  std::vector<int> values = {1, -1, 2, -1, 3};
  TreeNode* root = constructTree(values);
  vector<vector<int>> expected = {{1}, {2}, {3}};
  EXPECT_EQ(expected, solution.verticalTraversal(root));
}

TEST_P(VerticalOrderTraversalOfABinaryTreeTest, SamePositionSortByValue) {
  // 测试同一位置按值排序
  // 构造的树（层序遍历）：
  //       3
  //     /   \
  //    1     4
  //   / \   / \
  //  0   2 2   5
  std::vector<int> values = {
    3,
    1, 4,
    0, 2, 2, 5
  };
  TreeNode* root = constructTree(values);
  
  // 节点坐标分析：
  // 3: (0, 0)
  // 1: (1, -1), 4: (1, 1)
  // 0: (2, -2), 2: (2, 0), 2: (2, 0), 5: (2, 2)
  // 
  // 按列分组：
  // col -2: [0]
  // col -1: [1]
  // col 0: [3, 2, 2] (按行：第0行3，第2行2,2)
  // col 1: [4]
  // col 2: [5]
  vector<vector<int>> result = solution.verticalTraversal(root);
  EXPECT_EQ(5, result.size());
  EXPECT_EQ(vector<int>({0}), result[0]);      // col -2
  EXPECT_EQ(vector<int>({1}), result[1]);      // col -1
  EXPECT_EQ(vector<int>({3, 2, 2}), result[2]); // col 0 (按行排序，然后按值排序)
  EXPECT_EQ(vector<int>({4}), result[3]);      // col 1
  EXPECT_EQ(vector<int>({5}), result[4]);      // col 2
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, VerticalOrderTraversalOfABinaryTreeTest,
    ::testing::ValuesIn(VerticalOrderTraversalOfABinaryTreeSolution().getStrategyNames()));

}  // namespace problem_987
}  // namespace leetcode
