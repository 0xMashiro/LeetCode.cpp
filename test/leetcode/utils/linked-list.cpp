#include "leetcode/utils/linked-list.h"

#include "gtest/gtest.h"

namespace leetcode {
TEST(LeetCodeUtils, ListNodeConstructAndTraverse) {
  std::vector<int> nums = {2, 7, 11, 15};
  ListNode* head = constructLinkedList(nums);
  std::vector<int> result = traverse(head);
  EXPECT_EQ(nums, result);
}

TEST(LeetCodeUtils, ListNodeRemoveElementsCase1) {
  std::vector<int> nums = {2, 7, 11, 15};
  std::vector<int> expected = {2, 11, 15};
  ListNode* head = constructLinkedList(nums);
  std::vector<int> result = traverse(removeElements(head, 7));
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, ListNodeRemoveElementsCase2) {
  std::vector<int> nums = {2, 7, 11, 7};
  std::vector<int> expected = {2, 11};
  ListNode* head = constructLinkedList(nums);
  std::vector<int> result = traverse(removeElements(head, 7));
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, ListNodeRemoveElementsCase3) {
  std::vector<int> nums = {7, 7, 7, 7};
  std::vector<int> expected = {};
  ListNode* head = constructLinkedList(nums);
  std::vector<int> result = traverse(removeElements(head, 7));
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, ListNodeReverseListCase1) {
  std::vector<int> nums = {2, 7, 11, 15};
  std::vector<int> expected = {15, 11, 7, 2};
  ListNode* head = constructLinkedList(nums);
  std::vector<int> result = traverse(reverseList(head));
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, ListNodeReverseListCase2) {
  std::vector<int> nums = {2, 7};
  std::vector<int> expected = {7, 2};
  ListNode* head = constructLinkedList(nums);
  std::vector<int> result = traverse(reverseList(head));
  EXPECT_EQ(expected, result);
}

TEST(LeetCodeUtils, ListNodeGetNodeCase1) {
  std::vector<int> nums = {2, 7, 11, 15};
  ListNode* head = constructLinkedList(nums);
  ListNode* node = getNode(head, 0);
  EXPECT_EQ(2, node->val);
}

TEST(LeetCodeUtils, ListNodeGetNodeCase2) {
  std::vector<int> nums = {2, 7, 11, 15};
  ListNode* head = constructLinkedList(nums);
  ListNode* node = getNode(head, 1);
  EXPECT_EQ(7, node->val);
}

TEST(LeetCodeUtils, ListNodeGetNodeCase3) {
  std::vector<int> nums = {2, 7, 11, 15};
  ListNode* head = constructLinkedList(nums);
  ListNode* node = getNode(head, -1);
  EXPECT_EQ(nullptr, node);
}

TEST(LeetCodeUtils, ListNodeGetNodeCase4) {
  std::vector<int> nums = {2, 7, 11, 15};
  ListNode* head = constructLinkedList(nums);
  ListNode* node = getNode(head, 4);
  EXPECT_EQ(nullptr, node);
}

TEST(LeetCodeUtils, ListNodeGetTail) {
  std::vector<int> nums = {2, 7, 11, 15};
  ListNode* head = constructLinkedList(nums);
  ListNode* tail = getTail(head);
  EXPECT_EQ(15, tail->val);
}

TEST(LeetCodeUtils, LinkedListGet) {
  std::vector<int> nums = {2, 7, 11, 15};
  ListNode* head = constructLinkedList(nums);
  MyLinkedList linked_list(head);
  EXPECT_EQ(2, linked_list.get(0));
  EXPECT_EQ(7, linked_list.get(1));
  EXPECT_EQ(11, linked_list.get(2));
  EXPECT_EQ(15, linked_list.get(3));
}

TEST(LeetCodeUtils, LinkedListAddAtHead) {
  MyLinkedList linked_list;
  linked_list.addAtHead(1);
  linked_list.addAtHead(2);
  linked_list.addAtHead(3);
  EXPECT_EQ(3, linked_list.get(0));
  EXPECT_EQ(2, linked_list.get(1));
  EXPECT_EQ(1, linked_list.get(2));
}

TEST(LeetCodeUtils, LinkedListAddAtTail) {
  MyLinkedList linked_list;
  linked_list.addAtTail(1);
  linked_list.addAtTail(2);
  linked_list.addAtTail(3);
  EXPECT_EQ(1, linked_list.get(0));
  EXPECT_EQ(2, linked_list.get(1));
  EXPECT_EQ(3, linked_list.get(2));
}

TEST(LeetCodeUtils, LinkedListAddAtIndex) {
  MyLinkedList linked_list;
  linked_list.addAtHead(1);
  linked_list.addAtTail(3);
  linked_list.addAtIndex(1, 2);
  EXPECT_EQ(1, linked_list.get(0));
  EXPECT_EQ(2, linked_list.get(1));
  EXPECT_EQ(3, linked_list.get(2));
}

TEST(LeetCodeUtils, LinkedListDeleteAtIndexCase1) {
  MyLinkedList linked_list;
  linked_list.addAtHead(1);
  linked_list.addAtTail(3);
  linked_list.addAtIndex(1, 2);
  linked_list.deleteAtIndex(1);
  EXPECT_EQ(1, linked_list.get(0));
  EXPECT_EQ(3, linked_list.get(1));
}

TEST(LeetCodeUtils, LinkedListDeleteAtIndexCase2) {
  MyLinkedList linked_list;
  linked_list.addAtHead(1);
  linked_list.deleteAtIndex(0);
}
}  // namespace leetcode