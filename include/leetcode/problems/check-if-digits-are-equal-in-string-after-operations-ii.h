
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3463 {

using Func = std::function<bool(string)>;

class CheckIfDigitsAreEqualInStringAfterOperationsIiSolution : public SolutionBase<Func> {
 public:
  //! 3463. Check If Digits Are Equal in String After Operations II
  //! https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/
  bool hasSameDigits(string s);

  CheckIfDigitsAreEqualInStringAfterOperationsIiSolution();
};

}  // namespace problem_3463
}  // namespace leetcode
