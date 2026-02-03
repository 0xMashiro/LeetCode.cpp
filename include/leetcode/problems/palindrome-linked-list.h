
#include "leetcode/core.h"

namespace leetcode {
namespace problem_234 {

using Func = std::function<bool(ListNode*)>;

class PalindromeLinkedListSolution : public SolutionBase<Func> {
 public:
  //! 234. Palindrome Linked List
  //! https://leetcode.com/problems/palindrome-linked-list/
  bool isPalindrome(ListNode* head);

  PalindromeLinkedListSolution();
};

}  // namespace problem_234
}  // namespace leetcode
