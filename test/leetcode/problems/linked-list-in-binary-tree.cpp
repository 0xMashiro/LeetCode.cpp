
#include "leetcode/problems/linked-list-in-binary-tree.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1367 {

class LinkedListInBinaryTreeTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  LinkedListInBinaryTreeSolution solution;
};

TEST_P(LinkedListInBinaryTreeTest, Example1) {
  // head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
  // 注意：constructTree 使用 -1 表示 null
  ListNode* head = constructLinkedList({4, 2, 8});
  std::vector<int> treeValues = {1, 4, 4, -1, 2, 2, -1, 1, -1, 6, 8, -1, -1, -1, -1, 1, 3};
  TreeNode* root = constructTree(treeValues);
  EXPECT_TRUE(solution.isSubPath(head, root));
  // TreeNode 会自动析构，不需要手动 delete
}

TEST_P(LinkedListInBinaryTreeTest, Example2) {
  // head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
  ListNode* head = constructLinkedList({1, 4, 2, 6});
  std::vector<int> treeValues = {1, 4, 4, -1, 2, 2, -1, 1, -1, 6, 8, -1, -1, -1, -1, 1, 3};
  TreeNode* root = constructTree(treeValues);
  EXPECT_TRUE(solution.isSubPath(head, root));
}

TEST_P(LinkedListInBinaryTreeTest, Example3) {
  // head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
  ListNode* head = constructLinkedList({1, 4, 2, 6, 8});
  std::vector<int> treeValues = {1, 4, 4, -1, 2, 2, -1, 1, -1, 6, 8, -1, -1, -1, -1, 1, 3};
  TreeNode* root = constructTree(treeValues);
  EXPECT_FALSE(solution.isSubPath(head, root));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, LinkedListInBinaryTreeTest,
    ::testing::ValuesIn(LinkedListInBinaryTreeSolution().getStrategyNames()));

}  // namespace problem_1367
}  // namespace leetcode
