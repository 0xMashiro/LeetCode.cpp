#include "leetcode/problems/convert-binary-number-in-a-linked-list-to-integer.h"

namespace leetcode {
namespace problem_1290 {

/**
 * 遍历法：从左到右遍历链表，每次将当前结果乘以2再加上当前位
 * 时间复杂度: O(n)，空间复杂度: O(1)
 * n 为链表长度，最多30个节点
 */
static int solution1(ListNode* head) {
  int result = 0;
  while (head != nullptr) {
    result = (result << 1) | head->val;  // result = result * 2 + head->val
    head = head->next;
  }
  return result;
}

/**
 * 替代实现：使用 result * 2 + val 的形式，更易读
 * 时间复杂度: O(n)，空间复杂度: O(1)
 */
static int solution2(ListNode* head) {
  int result = 0;
  while (head != nullptr) {
    result = result * 2 + head->val;
    head = head->next;
  }
  return result;
}

ConvertBinaryNumberInALinkedListToIntegerSolution::ConvertBinaryNumberInALinkedListToIntegerSolution() {
  setMetaInfo({
    .id = 1290,
    .title = "Convert Binary Number in a Linked List to Integer",
    .url = "https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/"
  });
  registerStrategy("Bit Shift", solution1);
  registerStrategy("Arithmetic", solution2);
}

int ConvertBinaryNumberInALinkedListToIntegerSolution::getDecimalValue(ListNode* head) {
  return getSolution()(head);
}

}  // namespace problem_1290
}  // namespace leetcode
