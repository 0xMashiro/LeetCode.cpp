#include "leetcode/problems/split-linked-list-in-parts.h"

namespace leetcode {
namespace problem_725 {

// 先计算链表长度，然后均匀分配
// 时间复杂度: O(n), 空间复杂度: O(1)（不包括返回结果）
static vector<ListNode*> solution1(ListNode* head, int k) {
  // 计算链表长度
  int n = 0;
  ListNode* cur = head;
  while (cur != nullptr) {
    n++;
    cur = cur->next;
  }
  
  // 计算每部分的长度和额外分配的节点数
  int base_len = n / k;      // 每部分的基础长度
  int extra = n % k;         // 前 extra 个部分需要多分配一个节点
  
  vector<ListNode*> result;
  cur = head;
  
  for (int i = 0; i < k; i++) {
    result.push_back(cur);   // 当前部分的头节点
    
    // 计算当前部分的长度
    int part_len = base_len + (i < extra ? 1 : 0);
    
    // 移动到当前部分的末尾
    for (int j = 0; j < part_len - 1 && cur != nullptr; j++) {
      cur = cur->next;
    }
    
    // 断开连接，准备下一部分
    if (cur != nullptr) {
      ListNode* next_part = cur->next;
      cur->next = nullptr;   // 断开当前部分与下一部分的连接
      cur = next_part;
    }
  }
  
  return result;
}

SplitLinkedListInPartsSolution::SplitLinkedListInPartsSolution() {
  setMetaInfo({.id = 725,
               .title = "Split Linked List in Parts",
               .url = "https://leetcode.com/problems/split-linked-list-in-parts/"});
  registerStrategy("Count and Split", solution1);
}

vector<ListNode*> SplitLinkedListInPartsSolution::splitListToParts(ListNode* head, int k) {
  return getSolution()(head, k);
}

}  // namespace problem_725
}  // namespace leetcode
