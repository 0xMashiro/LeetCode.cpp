#include "leetcode/problems/split-linked-list-in-parts.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_725 {

class SplitLinkedListInPartsTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  SplitLinkedListInPartsSolution solution;
};

// 示例1: head = [1,2,3], k = 5
// 输出: [[1],[2],[3],[],[]]
TEST_P(SplitLinkedListInPartsTest, Example1) {
  ListNode* head = constructLinkedList({1, 2, 3});
  int k = 5;
  vector<ListNode*> result = solution.splitListToParts(head, k);
  
  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(traverse(result[0]), vector<int>({1}));
  EXPECT_EQ(traverse(result[1]), vector<int>({2}));
  EXPECT_EQ(traverse(result[2]), vector<int>({3}));
  EXPECT_EQ(traverse(result[3]), vector<int>());
  EXPECT_EQ(traverse(result[4]), vector<int>());
}

// 示例2: head = [1,2,3,4,5,6,7,8,9,10], k = 3
// 输出: [[1,2,3,4],[5,6,7],[8,9,10]]
TEST_P(SplitLinkedListInPartsTest, Example2) {
  ListNode* head = constructLinkedList({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  int k = 3;
  vector<ListNode*> result = solution.splitListToParts(head, k);
  
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(traverse(result[0]), vector<int>({1, 2, 3, 4}));
  EXPECT_EQ(traverse(result[1]), vector<int>({5, 6, 7}));
  EXPECT_EQ(traverse(result[2]), vector<int>({8, 9, 10}));
}

// 边界情况: 空链表
TEST_P(SplitLinkedListInPartsTest, EmptyList) {
  ListNode* head = nullptr;
  int k = 3;
  vector<ListNode*> result = solution.splitListToParts(head, k);
  
  EXPECT_EQ(result.size(), 3);
  for (int i = 0; i < k; i++) {
    EXPECT_EQ(result[i], nullptr);
  }
}

// 边界情况: 单节点链表
TEST_P(SplitLinkedListInPartsTest, SingleNode) {
  ListNode* head = constructLinkedList({1});
  int k = 1;
  vector<ListNode*> result = solution.splitListToParts(head, k);
  
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(traverse(result[0]), vector<int>({1}));
}

// 边界情况: k 大于链表长度
TEST_P(SplitLinkedListInPartsTest, KGreaterThanLength) {
  ListNode* head = constructLinkedList({1, 2});
  int k = 5;
  vector<ListNode*> result = solution.splitListToParts(head, k);
  
  EXPECT_EQ(result.size(), 5);
  EXPECT_EQ(traverse(result[0]), vector<int>({1}));
  EXPECT_EQ(traverse(result[1]), vector<int>({2}));
  EXPECT_EQ(traverse(result[2]), vector<int>());
  EXPECT_EQ(traverse(result[3]), vector<int>());
  EXPECT_EQ(traverse(result[4]), vector<int>());
}

// 边界情况: 链表长度刚好整除 k
TEST_P(SplitLinkedListInPartsTest, ExactDivision) {
  ListNode* head = constructLinkedList({1, 2, 3, 4, 5, 6});
  int k = 3;
  vector<ListNode*> result = solution.splitListToParts(head, k);
  
  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(traverse(result[0]), vector<int>({1, 2}));
  EXPECT_EQ(traverse(result[1]), vector<int>({3, 4}));
  EXPECT_EQ(traverse(result[2]), vector<int>({5, 6}));
}

// 边界情况: k = 1
TEST_P(SplitLinkedListInPartsTest, KEqualsOne) {
  ListNode* head = constructLinkedList({1, 2, 3, 4, 5});
  int k = 1;
  vector<ListNode*> result = solution.splitListToParts(head, k);
  
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(traverse(result[0]), vector<int>({1, 2, 3, 4, 5}));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, SplitLinkedListInPartsTest,
    ::testing::ValuesIn(SplitLinkedListInPartsSolution().getStrategyNames()));

}  // namespace problem_725
}  // namespace leetcode
