#include "leetcode/core.h"

namespace leetcode {
namespace problem_206 {

using Func = std::function<ListNode*(ListNode*)>;

class ReverseLinkedListSolution : public SolutionBase<Func> {
 public:
  //! 206. Reverse Linked List
  //! https://leetcode.com/problems/reverse-linked-list/
  ListNode* reverseList(ListNode* head);

  ReverseLinkedListSolution();
};

}  // namespace problem_206
}  // namespace leetcode
