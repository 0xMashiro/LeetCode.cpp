#include "leetcode/problems/next-greater-node-in-linked-list.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_1019 {

class NextGreaterNodeInLinkedListTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  NextGreaterNodeInLinkedListSolution solution;
};

TEST_P(NextGreaterNodeInLinkedListTest, Example1) {
  // Input: head = [2,1,5]
  // Output: [5,5,0]
  ListNode* head = constructLinkedList({2, 1, 5});
  vector<int> expected = {5, 5, 0};
  EXPECT_EQ(expected, solution.nextLargerNodes(head));
  // 注意：不要手动 delete head，会自动析构
}

TEST_P(NextGreaterNodeInLinkedListTest, Example2) {
  // Input: head = [2,7,4,3,5]
  // Output: [7,0,5,5,0]
  ListNode* head = constructLinkedList({2, 7, 4, 3, 5});
  vector<int> expected = {7, 0, 5, 5, 0};
  EXPECT_EQ(expected, solution.nextLargerNodes(head));
}

TEST_P(NextGreaterNodeInLinkedListTest, SingleElement) {
  // 边界：单元素，没有下一个更大值
  ListNode* head = constructLinkedList({5});
  vector<int> expected = {0};
  EXPECT_EQ(expected, solution.nextLargerNodes(head));
}

TEST_P(NextGreaterNodeInLinkedListTest, AllIncreasing) {
  // 递增序列
  ListNode* head = constructLinkedList({1, 2, 3, 4, 5});
  vector<int> expected = {2, 3, 4, 5, 0};
  EXPECT_EQ(expected, solution.nextLargerNodes(head));
}

TEST_P(NextGreaterNodeInLinkedListTest, AllDecreasing) {
  // 递减序列，没有下一个更大值
  ListNode* head = constructLinkedList({5, 4, 3, 2, 1});
  vector<int> expected = {0, 0, 0, 0, 0};
  EXPECT_EQ(expected, solution.nextLargerNodes(head));
}

TEST_P(NextGreaterNodeInLinkedListTest, AllSame) {
  // 全部相同，严格大于，所以没有下一个更大值
  ListNode* head = constructLinkedList({3, 3, 3, 3});
  vector<int> expected = {0, 0, 0, 0};
  EXPECT_EQ(expected, solution.nextLargerNodes(head));
}

TEST_P(NextGreaterNodeInLinkedListTest, LargerExample) {
  // 更多元素的测试
  ListNode* head = constructLinkedList({1, 7, 5, 1, 9, 2, 5, 1});
  vector<int> expected = {7, 9, 9, 9, 0, 5, 0, 0};
  EXPECT_EQ(expected, solution.nextLargerNodes(head));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, NextGreaterNodeInLinkedListTest,
    ::testing::ValuesIn(NextGreaterNodeInLinkedListSolution().getStrategyNames()));

}  // namespace problem_1019
}  // namespace leetcode
