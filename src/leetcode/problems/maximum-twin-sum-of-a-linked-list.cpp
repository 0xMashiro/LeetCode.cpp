#include "leetcode/problems/maximum-twin-sum-of-a-linked-list.h"

#include <algorithm>

namespace leetcode {
namespace problem_2130 {

// 快慢指针找中点 + 反转后半链表 + 同时遍历求最大孪生和
// 时间复杂度: O(n)，空间复杂度: O(1)
static int solution1(ListNode* head) {
  // 1. 快慢指针定位中点（后半链表起点）
  ListNode* slow = head;
  ListNode* fast = head;
  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }

  // 2. 反转后半链表
  ListNode* prev = nullptr;
  ListNode* curr = slow;
  while (curr != nullptr) {
    ListNode* next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  // 3. 同时遍历前半和反转后的后半，求最大孪生和
  int maxSum = 0;
  ListNode* first = head;
  ListNode* second = prev;  // prev 是反转后后半链表的头
  while (second != nullptr) {
    maxSum = std::max(maxSum, first->val + second->val);
    first = first->next;
    second = second->next;
  }

  return maxSum;
}

MaximumTwinSumOfALinkedListSolution::MaximumTwinSumOfALinkedListSolution() {
  setMetaInfo({.id = 2130,
               .title = "Maximum Twin Sum of a Linked List",
               .url = "https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/"});
  registerStrategy(
      {.name = "Reverse Second Half",
       .expected = "Accepted",
       .time_complexity = "O(n)",
       .space_complexity = "O(1)",
       .tags = {"Linked List", "Two Pointers"}},
      solution1);
}

int MaximumTwinSumOfALinkedListSolution::pairSum(ListNode* head) {
  return getSolution()(head);
}

}  // namespace problem_2130
}  // namespace leetcode
