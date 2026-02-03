#include "leetcode/core.h"

namespace leetcode {
namespace problem_2870 {

using Func = std::function<int(vector<int>&)>;

class MinimumNumberOfOperationsToMakeArrayEmptySolution : public SolutionBase<Func> {
 public:
  //! 2870. Minimum Number of Operations to Make Array Empty
  //! https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/
  int minOperations(vector<int>& nums);

  MinimumNumberOfOperationsToMakeArrayEmptySolution();
};

}  // namespace problem_2870
}  // namespace leetcode
