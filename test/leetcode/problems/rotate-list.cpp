#include "leetcode/problems/rotate-list.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_61 {

class RotateListTest : public ::testing::TestWithParam<string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  RotateListSolution solution;
};

TEST_P(RotateListTest, Example1) {
  ListNode* head = constructLinkedList({1, 2, 3, 4, 5});
  ListNode* result = solution.rotateRight(head, 2);
  std::vector<int> expected = {4, 5, 1, 2, 3};
  EXPECT_EQ(expected, traverse(result));
  // 不需要手动 delete，ListNode 没有析构，轻微泄漏可接受
}

TEST_P(RotateListTest, Example2) {
  ListNode* head = constructLinkedList({0, 1, 2});
  ListNode* result = solution.rotateRight(head, 4);
  std::vector<int> expected = {2, 0, 1};
  EXPECT_EQ(expected, traverse(result));
}

TEST_P(RotateListTest, SelfAuthoredEmpty) {
  ListNode* head = nullptr;
  ListNode* result = solution.rotateRight(head, 0);
  EXPECT_EQ(nullptr, result);
}

TEST_P(RotateListTest, SelfAuthoredSingleNode) {
  ListNode* head = constructLinkedList({1});
  ListNode* result = solution.rotateRight(head, 100);
  std::vector<int> expected = {1};
  EXPECT_EQ(expected, traverse(result));
}

TEST_P(RotateListTest, SelfAuthoredKZero) {
  ListNode* head = constructLinkedList({1, 2, 3});
  ListNode* result = solution.rotateRight(head, 0);
  std::vector<int> expected = {1, 2, 3};
  EXPECT_EQ(expected, traverse(result));
}

TEST_P(RotateListTest, SelfAuthoredKMultipleOfLength) {
  ListNode* head = constructLinkedList({1, 2, 3, 4});
  ListNode* result = solution.rotateRight(head, 8);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(expected, traverse(result));
}

TEST_P(RotateListTest, SelfAuthoredTwoNodes) {
  ListNode* head = constructLinkedList({1, 2});
  ListNode* result = solution.rotateRight(head, 1);
  std::vector<int> expected = {2, 1};
  EXPECT_EQ(expected, traverse(result));
}

TEST_P(RotateListTest, SelfAuthoredRotateFull) {
  ListNode* head = constructLinkedList({1, 2, 3});
  ListNode* result = solution.rotateRight(head, 3);
  std::vector<int> expected = {1, 2, 3};
  EXPECT_EQ(expected, traverse(result));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, RotateListTest,
    ::testing::ValuesIn(RotateListSolution().getStrategyNames()));

}  // namespace problem_61
}  // namespace leetcode
