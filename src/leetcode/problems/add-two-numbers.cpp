#include "leetcode/problems/add-two-numbers.h"

namespace leetcode {
namespace problem_2 {

// 模拟竖式加法（迭代解法）
// 时间复杂度: O(max(m,n)), 空间复杂度: O(max(m,n))
static ListNode* solution1(ListNode* l1, ListNode* l2) {
  ListNode dummy(0);
  ListNode* current = &dummy;
  int carry = 0;

  while (l1 != nullptr || l2 != nullptr || carry != 0) {
    int sum = carry;

    if (l1 != nullptr) {
      sum += l1->val;
      l1 = l1->next;
    }

    if (l2 != nullptr) {
      sum += l2->val;
      l2 = l2->next;
    }

    carry = sum / 10;
    current->next = new ListNode(sum % 10);
    current = current->next;
  }

  return dummy.next;
}

// 递归解法（使用 lambda 递归）
// 时间复杂度: O(max(m,n)), 空间复杂度: O(max(m,n))（递归栈空间）
static ListNode* solution2(ListNode* l1, ListNode* l2) {
  std::function<ListNode*(ListNode*, ListNode*, int)> add =
      [&](ListNode* l1, ListNode* l2, int carry) -> ListNode* {
    if (l1 == nullptr && l2 == nullptr && carry == 0) {
      return nullptr;
    }

    int sum = carry;
    if (l1 != nullptr) {
      sum += l1->val;
      l1 = l1->next;
    }

    if (l2 != nullptr) {
      sum += l2->val;
      l2 = l2->next;
    }

    ListNode* node = new ListNode(sum % 10);
    node->next = add(l1, l2, sum / 10);
    return node;
  };

  return add(l1, l2, 0);
}

AddTwoNumbersSolution::AddTwoNumbersSolution() {
  setMetaInfo({.id = 2,
               .title = "Add Two Numbers",
               .url = "https://leetcode.com/problems/add-two-numbers"});
  registerStrategy({.name = "Iterative Addition"}, solution1);
  registerStrategy({.name = "Recursive Addition"}, solution2);
}

ListNode* AddTwoNumbersSolution::addTwoNumbers(ListNode* l1, ListNode* l2) {
  return getSolution()(l1, l2);
}

}  // namespace problem_2
}  // namespace leetcode