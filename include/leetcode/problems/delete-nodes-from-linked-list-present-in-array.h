
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3217 {

using Func = std::function<ListNode*(vector<int>&, ListNode*)>;

class DeleteNodesFromLinkedListPresentInArraySolution : public SolutionBase<Func> {
 public:
  //! 3217. Delete Nodes From Linked List Present in Array
  //! https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/
  ListNode* modifiedList(vector<int>& nums, ListNode* head);

  DeleteNodesFromLinkedListPresentInArraySolution();
};

}  // namespace problem_3217
}  // namespace leetcode
