
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1461 {

using Func = std::function<bool(string, int)>;

class CheckIfAStringContainsAllBinaryCodesOfSizeKSolution : public SolutionBase<Func> {
 public:
  //! 1461. Check If a String Contains All Binary Codes of Size K
  //! https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/
  bool hasAllCodes(string s, int k);

  CheckIfAStringContainsAllBinaryCodesOfSizeKSolution();
};

}  // namespace problem_1461
}  // namespace leetcode
