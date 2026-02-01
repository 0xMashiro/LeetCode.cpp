#include "leetcode/core.h"

namespace leetcode {
namespace problem_725 {

using Func = std::function<vector<ListNode*>(ListNode*, int)>;

class SplitLinkedListInPartsSolution : public SolutionBase<Func> {
 public:
  //! 725. Split Linked List in Parts
  //! https://leetcode.com/problems/split-linked-list-in-parts/
  vector<ListNode*> splitListToParts(ListNode* head, int k);

  SplitLinkedListInPartsSolution();
};

}  // namespace problem_725
}  // namespace leetcode
