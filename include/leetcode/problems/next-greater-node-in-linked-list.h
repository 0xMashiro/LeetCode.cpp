#include "leetcode/core.h"

namespace leetcode {
namespace problem_1019 {

using Func = std::function<vector<int>(ListNode*)>;

class NextGreaterNodeInLinkedListSolution : public SolutionBase<Func> {
 public:
  //! 1019. Next Greater Node In Linked List
  //! https://leetcode.com/problems/next-greater-node-in-linked-list/
  vector<int> nextLargerNodes(ListNode* head);

  NextGreaterNodeInLinkedListSolution();
};

}  // namespace problem_1019
}  // namespace leetcode
