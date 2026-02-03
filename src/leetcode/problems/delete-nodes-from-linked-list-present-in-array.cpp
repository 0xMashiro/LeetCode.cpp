
#include "leetcode/problems/delete-nodes-from-linked-list-present-in-array.h"

namespace leetcode {
namespace problem_3217 {

// 哈希集合 + 哑节点
// 时间复杂度: O(n + m)，其中 n 是 nums 长度，m 是链表长度
// 空间复杂度: O(n)，哈希集合存储空间
static ListNode* solution1(vector<int>& nums, ListNode* head) {
  // 将 nums 放入哈希集合，实现 O(1) 查找
  unordered_set<int> toRemove(nums.begin(), nums.end());
  
  // 使用哑节点处理头节点可能被删除的情况
  ListNode dummy(0, head);
  ListNode* prev = &dummy;
  ListNode* cur = head;
  
  while (cur != nullptr) {
    if (toRemove.find(cur->val) != toRemove.end()) {
      // 当前节点需要删除
      prev->next = cur->next;
      // 不移动 prev，继续检查下一个节点
    } else {
      // 当前节点保留，移动 prev
      prev = cur;
    }
    cur = cur->next;
  }
  
  return dummy.next;
}

DeleteNodesFromLinkedListPresentInArraySolution::DeleteNodesFromLinkedListPresentInArraySolution() {
  setMetaInfo({.id = 3217,
               .title = "Delete Nodes From Linked List Present in Array",
               .url = "https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/"});
  registerStrategy("Hash Set + Dummy Node", solution1);
}

ListNode* DeleteNodesFromLinkedListPresentInArraySolution::modifiedList(vector<int>& nums, ListNode* head) {
  return getSolution()(nums, head);
}

}  // namespace problem_3217
}  // namespace leetcode
