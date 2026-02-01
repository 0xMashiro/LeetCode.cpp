#include "leetcode/core.h"

namespace leetcode {
namespace problem_2844 {

using Func = std::function<int(string)>;

class MinimumOperationsToMakeASpecialNumberSolution : public SolutionBase<Func> {
 public:
  //! 2844. Minimum Operations to Make a Special Number
  //! https://leetcode.com/problems/minimum-operations-to-make-a-special-number/
  int minimumOperations(string num);

  MinimumOperationsToMakeASpecialNumberSolution();
};

}  // namespace problem_2844
}  // namespace leetcode
