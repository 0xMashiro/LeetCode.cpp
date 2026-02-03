#include "leetcode/problems/reverse-nodes-in-even-length-groups.h"

namespace leetcode {
namespace problem_2074 {

// 反转从 head 开始的 n 个节点，返回新的头节点和尾节点
// 假设链表至少有 n 个节点
static std::pair<ListNode*, ListNode*> reverseN(ListNode* head, int n) {
  ListNode* prev = nullptr;
  ListNode* cur = head;
  for (int i = 0; i < n; ++i) {
    ListNode* next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  // prev 是新的头，head 是新的尾
  return {prev, head};
}

// 主解法：按组遍历，偶数长度组反转
static ListNode* solution1(ListNode* head) {
  if (!head || !head->next) return head;
  
  ListNode dummy(0, head);
  ListNode* prev_tail = &dummy;  // 上一组的尾节点
  ListNode* cur = head;
  int group_num = 1;  // 当前组号，也是期望的组长度
  
  while (cur) {
    // 确定当前组的实际长度
    int actual_len = 0;
    ListNode* temp = cur;
    for (int i = 0; i < group_num && temp; ++i) {
      temp = temp->next;
      actual_len++;
    }
    
    // 如果实际长度为0，说明没有节点了，退出
    if (actual_len == 0) break;
    
    // 记录当前组的起始节点和下一组的起始节点
    ListNode* group_start = cur;
    
    // 移动到当前组的最后一个节点
    ListNode* group_end = cur;
    for (int i = 1; i < actual_len; ++i) {
      group_end = group_end->next;
    }
    ListNode* next_group_start = group_end->next;
    
    if (actual_len % 2 == 0) {
      // 偶数长度，需要反转
      // 断开与下一组的连接
      group_end->next = nullptr;
      // 反转当前组
      auto [new_head, new_tail] = reverseN(group_start, actual_len);
      // 重新连接
      prev_tail->next = new_head;
      new_tail->next = next_group_start;
      // 更新 prev_tail
      prev_tail = new_tail;
    } else {
      // 奇数长度，不反转
      prev_tail = group_end;
    }
    
    // 移动到下一组
    cur = next_group_start;
    group_num++;
  }
  
  return dummy.next;
}

ReverseNodesInEvenLengthGroupsSolution::ReverseNodesInEvenLengthGroupsSolution() {
  setMetaInfo({.id = 2074,
               .title = "Reverse Nodes in Even Length Groups",
               .url = "https://leetcode.com/problems/reverse-nodes-in-even-length-groups/"});
  registerStrategy("Group Reverse", solution1);
}

ListNode* ReverseNodesInEvenLengthGroupsSolution::reverseEvenLengthGroups(ListNode* head) {
  return getSolution()(head);
}

}  // namespace problem_2074
}  // namespace leetcode
