#include "leetcode/core.h"

namespace leetcode {
namespace problem_2074 {

using Func = std::function<ListNode*(ListNode*)>;

class ReverseNodesInEvenLengthGroupsSolution : public SolutionBase<Func> {
 public:
  //! 2074. Reverse Nodes in Even Length Groups
  //! https://leetcode.com/problems/reverse-nodes-in-even-length-groups/
  ListNode* reverseEvenLengthGroups(ListNode* head);

  ReverseNodesInEvenLengthGroupsSolution();
};

}  // namespace problem_2074
}  // namespace leetcode
