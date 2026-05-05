#include "leetcode/problems/rotate-list.h"

namespace leetcode {
namespace problem_61 {

// 成环法：先遍历求长度，尾连头成环，再在合适位置断开
// 时间复杂度: O(n), 空间复杂度: O(1)
static ListNode* solution1(ListNode* head, int k) {
  if (!head || !head->next) return head;

  // 遍历求长度，同时找到尾节点
  int n = 1;
  ListNode* tail = head;
  while (tail->next) {
    tail = tail->next;
    ++n;
  }

  // 取模，减少不必要的旋转
  k %= n;
  if (k == 0) return head;

  // 成环
  tail->next = head;

  // 找到新链表的尾节点，它在原头后面 n - k - 1 步
  int steps = n - k - 1;
  ListNode* newTail = head;
  for (int i = 0; i < steps; ++i) {
    newTail = newTail->next;
  }

  // 新头是新尾的下一个节点，断开成单向链表
  ListNode* newHead = newTail->next;
  newTail->next = nullptr;

  return newHead;
}

// 双指针法：快指针先走 k 步，然后快慢一起走直到快指针到尾
// 时间复杂度: O(n), 空间复杂度: O(1)
static ListNode* solution2(ListNode* head, int k) {
  if (!head || !head->next) return head;

  // 遍历求长度
  int n = 1;
  ListNode* tail = head;
  while (tail->next) {
    tail = tail->next;
    ++n;
  }

  k %= n;
  if (k == 0) return head;

  // 快指针先走 k 步
  ListNode* fast = head;
  for (int i = 0; i < k; ++i) {
    fast = fast->next;
  }

  // 快慢指针一起走，直到 fast 到达尾节点
  ListNode* slow = head;
  while (fast->next) {
    fast = fast->next;
    slow = slow->next;
  }

  // 此时 slow 是倒数第 k+1 个节点，fast 是尾节点
  // fast 指向原头，新头是 slow->next，slow->next 设为 nullptr
  ListNode* newHead = slow->next;
  slow->next = nullptr;
  fast->next = head;

  return newHead;
}

RotateListSolution::RotateListSolution() {
  setMetaInfo({.id = 61,
               .title = "Rotate List",
               .url = "https://leetcode.com/problems/rotate-list/"});
  registerStrategy("Close Loop", solution1);
  registerStrategy("Two Pointers", solution2);
}

ListNode* RotateListSolution::rotateRight(ListNode* head, int k) {
  return getSolution()(head, k);
}

}  // namespace problem_61
}  // namespace leetcode
