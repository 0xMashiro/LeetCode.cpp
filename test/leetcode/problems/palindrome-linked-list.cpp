
#include "leetcode/problems/palindrome-linked-list.h"

#include "gtest/gtest.h"

namespace leetcode {
namespace problem_234 {

class PalindromeLinkedListTest : public ::testing::TestWithParam<std::string> {
 protected:
  void SetUp() override { solution.setStrategy(GetParam()); }

  PalindromeLinkedListSolution solution;
};

TEST_P(PalindromeLinkedListTest, Example1) {
  // Input: head = [1,2,2,1], Output: true
  ListNode* head = constructLinkedList({1, 2, 2, 1});
  EXPECT_TRUE(solution.isPalindrome(head));
}

TEST_P(PalindromeLinkedListTest, Example2) {
  // Input: head = [1,2], Output: false
  ListNode* head = constructLinkedList({1, 2});
  EXPECT_FALSE(solution.isPalindrome(head));
}

TEST_P(PalindromeLinkedListTest, SingleNode) {
  // 边界：单节点链表是回文
  ListNode* head = constructLinkedList({1});
  EXPECT_TRUE(solution.isPalindrome(head));
}

TEST_P(PalindromeLinkedListTest, OddLengthPalindrome) {
  // 奇数长度回文
  ListNode* head = constructLinkedList({1, 2, 3, 2, 1});
  EXPECT_TRUE(solution.isPalindrome(head));
}

TEST_P(PalindromeLinkedListTest, OddLengthNotPalindrome) {
  // 奇数长度非回文
  ListNode* head = constructLinkedList({1, 2, 3, 4, 5});
  EXPECT_FALSE(solution.isPalindrome(head));
}

TEST_P(PalindromeLinkedListTest, AllSameElements) {
  // 所有元素相同
  ListNode* head = constructLinkedList({1, 1, 1, 1});
  EXPECT_TRUE(solution.isPalindrome(head));
}

INSTANTIATE_TEST_SUITE_P(
    LeetCode, PalindromeLinkedListTest,
    ::testing::ValuesIn(PalindromeLinkedListSolution().getStrategyNames()));

}  // namespace problem_234
}  // namespace leetcode
