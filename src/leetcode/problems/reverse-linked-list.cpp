#include "leetcode/problems/reverse-linked-list.h"

namespace leetcode {
namespace problem_206 {

// 迭代法：三指针法
// 时间复杂度: O(n), 空间复杂度: O(1)
static ListNode* solution1(ListNode* head) {
  ListNode* prev = nullptr;
  ListNode* curr = head;
  ListNode* next = nullptr;
  
  while (curr != nullptr) {
    next = curr->next;  // 暂存下一个节点
    curr->next = prev;  // 反转当前节点的指向
    prev = curr;        // prev 前移
    curr = next;        // curr 前移
  }
  
  return prev;  // prev 指向新的头节点
}

// 递归法
// 时间复杂度: O(n), 空间复杂度: O(n)（递归栈）
static ListNode* solution2(ListNode* head) {
  // 基本情况：空链表或只有一个节点
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  
  // 递归反转剩余链表
  ListNode* newHead = solution2(head->next);
  
  // 反转当前节点与下一个节点的关系
  head->next->next = head;
  head->next = nullptr;
  
  return newHead;
}

ReverseLinkedListSolution::ReverseLinkedListSolution() {
  setMetaInfo({.id = 206,
               .title = "Reverse Linked List",
               .url = "https://leetcode.com/problems/reverse-linked-list/"});
  registerStrategy("Iterative", solution1);
  registerStrategy("Recursive", solution2);
}

ListNode* ReverseLinkedListSolution::reverseList(ListNode* head) {
  return getSolution()(head);
}

}  // namespace problem_206
}  // namespace leetcode
