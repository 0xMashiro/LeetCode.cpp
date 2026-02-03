#include "leetcode/problems/reverse-nodes-in-even-length-groups.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_2074 {

class ReverseNodesInEvenLengthGroupsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  ReverseNodesInEvenLengthGroupsSolution solution;
};

TEST_P(ReverseNodesInEvenLengthGroupsTest, Example1) {
  // Input: head = [5,2,6,3,9,1,7,3,8,4]
  // Output: [5,6,2,3,9,1,4,8,3,7]
  ListNode* head = constructLinkedList({5, 2, 6, 3, 9, 1, 7, 3, 8, 4});
  ListNode* result = solution.reverseEvenLengthGroups(head);
  EXPECT_EQ(traverse(result), std::vector<int>({5, 6, 2, 3, 9, 1, 4, 8, 3, 7}));
}

TEST_P(ReverseNodesInEvenLengthGroupsTest, Example2) {
  // Input: head = [1,1,0,6]
  // Output: [1,0,1,6]
  ListNode* head = constructLinkedList({1, 1, 0, 6});
  ListNode* result = solution.reverseEvenLengthGroups(head);
  EXPECT_EQ(traverse(result), std::vector<int>({1, 0, 1, 6}));
}

TEST_P(ReverseNodesInEvenLengthGroupsTest, Example3) {
  // Input: head = [1,1,0,6,5]
  // Output: [1,0,1,5,6]
  ListNode* head = constructLinkedList({1, 1, 0, 6, 5});
  ListNode* result = solution.reverseEvenLengthGroups(head);
  EXPECT_EQ(traverse(result), std::vector<int>({1, 0, 1, 5, 6}));
}

TEST_P(ReverseNodesInEvenLengthGroupsTest, SingleNode) {
  // 只有一个节点
  ListNode* head = constructLinkedList({1});
  ListNode* result = solution.reverseEvenLengthGroups(head);
  EXPECT_EQ(traverse(result), std::vector<int>({1}));
}

TEST_P(ReverseNodesInEvenLengthGroupsTest, TwoNodes) {
  // 两个节点，第2组长度为1（实际）或2（期望），实际是1（奇数）不反转
  // 组1: [1] - 长度1（奇数，不反转）
  // 组2: [2] - 实际长度1（奇数，不反转）
  ListNode* head = constructLinkedList({1, 2});
  ListNode* result = solution.reverseEvenLengthGroups(head);
  EXPECT_EQ(traverse(result), std::vector<int>({1, 2}));
}

TEST_P(ReverseNodesInEvenLengthGroupsTest, ThreeNodes) {
  // 三个节点
  // 组1: [1] - 长度1（奇数，不反转）
  // 组2: [2,3] - 长度2（偶数，反转）-> [3,2]
  ListNode* head = constructLinkedList({1, 2, 3});
  ListNode* result = solution.reverseEvenLengthGroups(head);
  EXPECT_EQ(traverse(result), std::vector<int>({1, 3, 2}));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, ReverseNodesInEvenLengthGroupsTest,
    ::testing::ValuesIn(ReverseNodesInEvenLengthGroupsSolution().getStrategyNames()));

}  // namespace problem_2074
}  // namespace leetcode
