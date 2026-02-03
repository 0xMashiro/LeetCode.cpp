
#include "leetcode/problems/palindrome-linked-list.h"

namespace leetcode {
namespace problem_234 {

// 快慢指针 + 反转后半部分链表
// 时间复杂度: O(n), 空间复杂度: O(1)
static bool solution1(ListNode* head) {
  if (!head || !head->next) {
    return true;
  }

  // 1. 使用快慢指针找到中点
  // slow 最终指向后半部分的开头（奇数长度时，slow 指向中间节点）
  ListNode* slow = head;
  ListNode* fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  // 2. 反转后半部分链表
  // prev 是反转后的新头节点
  ListNode* prev = nullptr;
  ListNode* cur = slow;
  while (cur) {
    ListNode* next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }

  // 3. 比较前半部分和反转后的后半部分
  ListNode* left = head;
  ListNode* right = prev;
  bool isPalin = true;
  while (right) {  // right 是后半部分（较短或等长）
    if (left->val != right->val) {
      isPalin = false;
      break;
    }
    left = left->next;
    right = right->next;
  }

  return isPalin;
}

PalindromeLinkedListSolution::PalindromeLinkedListSolution() {
  setMetaInfo({.id = 234,
               .title = "Palindrome Linked List",
               .url = "https://leetcode.com/problems/palindrome-linked-list/"});
  registerStrategy("Fast Slow Pointer + Reverse", solution1);
}

bool PalindromeLinkedListSolution::isPalindrome(ListNode* head) {
  return getSolution()(head);
}

}  // namespace problem_234
}  // namespace leetcode
