#include "leetcode/core.h"

namespace leetcode {
namespace problem_3396 {

using Func = std::function<int(vector<int>&)>;

class MinimumNumberOfOperationsToMakeElementsInArrayDistinctSolution : public SolutionBase<Func> {
 public:
  //! 3396. Minimum Number of Operations to Make Elements in Array Distinct
  //! https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/
  int minimumOperations(vector<int>& nums);

  MinimumNumberOfOperationsToMakeElementsInArrayDistinctSolution();
};

}  // namespace problem_3396
}  // namespace leetcode
