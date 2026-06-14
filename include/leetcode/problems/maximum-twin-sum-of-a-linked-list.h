#include "leetcode/core.h"

namespace leetcode {
namespace problem_2130 {

using Func = std::function<int(ListNode*)>;

class MaximumTwinSumOfALinkedListSolution : public SolutionBase<Func> {
 public:
  MaximumTwinSumOfALinkedListSolution();

  int pairSum(ListNode* head);
};

}  // namespace problem_2130
}  // namespace leetcode
