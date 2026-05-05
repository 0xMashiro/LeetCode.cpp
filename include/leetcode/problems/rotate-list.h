#include "leetcode/core.h"

namespace leetcode {
namespace problem_61 {

using Func = std::function<ListNode*(ListNode*, int)>;

class RotateListSolution : public SolutionBase<Func> {
 public:
  //! 61. Rotate List
  //! https://leetcode.com/problems/rotate-list/
  ListNode* rotateRight(ListNode* head, int k);

  RotateListSolution();
};

}  // namespace problem_61
}  // namespace leetcode
