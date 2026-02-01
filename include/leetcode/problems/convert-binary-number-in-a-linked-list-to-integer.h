#include "leetcode/core.h"

namespace leetcode {
namespace problem_1290 {

using Func = std::function<int(ListNode*)>;

class ConvertBinaryNumberInALinkedListToIntegerSolution : public SolutionBase<Func> {
 public:
  //! 1290. Convert Binary Number in a Linked List to Integer
  //! https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
  int getDecimalValue(ListNode* head);

  ConvertBinaryNumberInALinkedListToIntegerSolution();
};

}  // namespace problem_1290
}  // namespace leetcode
