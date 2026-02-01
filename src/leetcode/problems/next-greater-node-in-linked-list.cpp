#include "leetcode/problems/next-greater-node-in-linked-list.h"

namespace leetcode {
namespace problem_1019 {

// 单调栈解法
// 先将链表转换为数组，然后使用单调递减栈找到每个元素的下一个更大值
// 时间复杂度: O(n), 空间复杂度: O(n)
static vector<int> solution1(ListNode* head) {
  // 将链表转换为数组，同时记录值
  vector<int> values;
  ListNode* cur = head;
  while (cur != nullptr) {
    values.push_back(cur->val);
    cur = cur->next;
  }
  
  int n = values.size();
  vector<int> result(n, 0);  // 默认为0（找不到下一个更大值的情况）
  vector<int> stack;  // 单调递减栈，存储索引
  
  for (int i = 0; i < n; ++i) {
    // 当当前值大于栈顶索引对应的值时，找到下一个更大值
    while (!stack.empty() && values[stack.back()] < values[i]) {
      result[stack.back()] = values[i];
      stack.pop_back();
    }
    stack.push_back(i);
  }
  
  return result;
}

NextGreaterNodeInLinkedListSolution::NextGreaterNodeInLinkedListSolution() {
  setMetaInfo({.id = 1019,
               .title = "Next Greater Node In Linked List",
               .url = "https://leetcode.com/problems/next-greater-node-in-linked-list/"});
  registerStrategy("Monotonic Stack", solution1);
}

vector<int> NextGreaterNodeInLinkedListSolution::nextLargerNodes(ListNode* head) {
  return getSolution()(head);
}

}  // namespace problem_1019
}  // namespace leetcode
