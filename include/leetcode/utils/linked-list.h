#ifndef LEETCODE_UTILS_LINKED_LIST_H__
#define LEETCODE_UTILS_LINKED_LIST_H__

#include <vector>

namespace leetcode {

//! Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;

  ListNode() : val(0), next(nullptr) {}

  ListNode(int x) : val(x), next(nullptr) {}

  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//! Constructing a linked list from a vector
ListNode* constructLinkedList(const std::vector<int>& nums);

//! Traversing the linked list
std::vector<int> traverse(ListNode* head);

//! Remove all elements from a linked list of integers that have value val.
ListNode* removeElements(ListNode* head, int val);

//! Reverse a singly linked list.
ListNode* reverseList(ListNode* head);

//! Get the node at the given index
ListNode* getNode(ListNode* head, int index);

//! Get the tail of the linked list
ListNode* getTail(ListNode* head);

class MyLinkedList {
 public:
  MyLinkedList() : head(nullptr), tail(nullptr), dummy(0), size(0) {}

  MyLinkedList(ListNode* head);
  ~MyLinkedList();

  int get(int index);

  void addAtHead(int val);

  void addAtTail(int val);

  void addAtIndex(int index, int val);

  void deleteAtIndex(int index);

 private:
  ListNode* head = nullptr;
  ListNode* tail = nullptr;
  ListNode dummy;
  int size = 0;

  ListNode* getNode(int index);
};
}  // namespace leetcode
#endif  // LEETCODE_UTILS_LINKED_LIST_H__