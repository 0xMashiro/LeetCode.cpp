/**
 * Test cases for 1530. Number of Good Leaf Nodes Pairs
 */

#include "leetcode/problems/number-of-good-leaf-nodes-pairs.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1530 {

class NumberOfGoodLeafNodesPairsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NumberOfGoodLeafNodesPairsSolution solution;
};

// Example 1: root = [1,2,3,null,4], distance = 3, Output: 1
// Tree structure:
//      1
//     / \
//    2   3
//     \
//      4
// Leaf nodes: 3 and 4, path length: 3 (4->2->1->3)
TEST_P(NumberOfGoodLeafNodesPairsTest, Example1) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3, -1, 4});
  int distance = 3;
  EXPECT_EQ(1, solution.countPairs(root, distance));
  // Note: root will be automatically deleted by TreeNode destructor
}

// Example 2: root = [1,2,3,4,5,6,7], distance = 3, Output: 2
// Tree structure:
//        1
//      /   \
//     2     3
//    / \   / \
//   4   5 6   7
// Good pairs: [4,5] and [6,7] with distance 2
TEST_P(NumberOfGoodLeafNodesPairsTest, Example2) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3, 4, 5, 6, 7});
  int distance = 3;
  EXPECT_EQ(2, solution.countPairs(root, distance));
}

// Example 3: root = [7,1,4,6,null,5,3,null,null,null,null,null,2], distance = 3, Output: 1
TEST_P(NumberOfGoodLeafNodesPairsTest, Example3) {
  TreeNode* root = constructTree(std::vector<int>{7, 1, 4, 6, -1, 5, 3, -1, -1, -1, -1, -1, 2});
  int distance = 3;
  EXPECT_EQ(1, solution.countPairs(root, distance));
}

// Edge case: Single node (not a leaf pair possible)
TEST_P(NumberOfGoodLeafNodesPairsTest, SingleNode) {
  TreeNode* root = constructTree(std::vector<int>{1});
  int distance = 3;
  EXPECT_EQ(0, solution.countPairs(root, distance));
}

// Edge case: Two leaf nodes directly connected to root
TEST_P(NumberOfGoodLeafNodesPairsTest, TwoLeaves) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3});
  int distance = 2;
  EXPECT_EQ(1, solution.countPairs(root, distance));  // Path: 2->1->3, length 2
}

// Edge case: distance = 1, only adjacent leaves count (but leaves are never adjacent)
TEST_P(NumberOfGoodLeafNodesPairsTest, DistanceOne) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3, 4, 5, 6, 7});
  int distance = 1;
  EXPECT_EQ(0, solution.countPairs(root, distance));  // Minimum distance between leaves is 2
}

// Edge case: Large distance, all pairs are good
// Tree with 4 leaves, C(4,2) = 6 pairs
TEST_P(NumberOfGoodLeafNodesPairsTest, LargeDistance) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3, 4, 5, 6, 7});
  int distance = 10;
  EXPECT_EQ(6, solution.countPairs(root, distance));  // All 6 pairs are good
}

// Edge case: Chain tree (linear structure)
// 1->2->3->4->5, only one leaf (5), no pairs possible
TEST_P(NumberOfGoodLeafNodesPairsTest, ChainTree) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, -1, 3, -1, 4, -1, 5});
  int distance = 10;
  EXPECT_EQ(0, solution.countPairs(root, distance));  // Only one leaf node
}

// Edge case: distance = 2
TEST_P(NumberOfGoodLeafNodesPairsTest, DistanceTwo) {
  TreeNode* root = constructTree(std::vector<int>{1, 2, 3, 4, 5, 6, 7});
  int distance = 2;
  EXPECT_EQ(2, solution.countPairs(root, distance));  // Only sibling pairs
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NumberOfGoodLeafNodesPairsTest,
    ::testing::ValuesIn(NumberOfGoodLeafNodesPairsSolution().getStrategyNames()));

}  // namespace problem_1530
}  // namespace leetcode
