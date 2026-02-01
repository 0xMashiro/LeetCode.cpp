
#include "leetcode/problems/longest-zigzag-path-in-a-binary-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1372 {

class LongestZigzagPathInABinaryTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LongestZigzagPathInABinaryTreeSolution solution;
};

TEST_P(LongestZigzagPathInABinaryTreeTest, Example1) {
  // Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1]
  // Output: 3
  std::vector<int> values = {1, -1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, -1, -1, 1};
  auto root = constructTree(values);
  EXPECT_EQ(3, solution.longestZigZag(root));
}

TEST_P(LongestZigzagPathInABinaryTreeTest, Example2) {
  // Input: root = [1,1,1,null,1,null,null,1,1,null,1]
  // Output: 4
  std::vector<int> values = {1, 1, 1, -1, 1, -1, -1, 1, 1, -1, 1};
  auto root = constructTree(values);
  EXPECT_EQ(4, solution.longestZigZag(root));
}

TEST_P(LongestZigzagPathInABinaryTreeTest, Example3) {
  // Input: root = [1]
  // Output: 0
  std::vector<int> values = {1};
  auto root = constructTree(values);
  EXPECT_EQ(0, solution.longestZigZag(root));
}

TEST_P(LongestZigzagPathInABinaryTreeTest, TwoNodes) {
  // 两个节点: [1,2]
  // Output: 1
  std::vector<int> values = {1, 2};
  auto root = constructTree(values);
  EXPECT_EQ(1, solution.longestZigZag(root));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LongestZigzagPathInABinaryTreeTest,
    ::testing::ValuesIn(LongestZigzagPathInABinaryTreeSolution().getStrategyNames()));

}  // namespace problem_1372
}  // namespace leetcode
