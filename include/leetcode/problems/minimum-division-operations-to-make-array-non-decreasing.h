#include "leetcode/core.h"

namespace leetcode {
namespace problem_3326 {

using Func = std::function<int(vector<int>&)>;

class MinimumDivisionOperationsToMakeArrayNonDecreasingSolution : public SolutionBase<Func> {
 public:
  int minOperations(vector<int>& nums);

  MinimumDivisionOperationsToMakeArrayNonDecreasingSolution();
};

}  // namespace problem_3326
}  // namespace leetcode
