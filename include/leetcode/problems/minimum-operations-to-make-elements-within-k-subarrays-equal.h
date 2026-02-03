#include "leetcode/core.h"

namespace leetcode {
namespace problem_3505 {

using Func = std::function<long long(vector<int>&, int, int)>;

class MinimumOperationsToMakeElementsWithinKSubarraysEqualSolution : public SolutionBase<Func> {
 public:
  long long minOperations(vector<int>& nums, int x, int k);

  MinimumOperationsToMakeElementsWithinKSubarraysEqualSolution();
};

}  // namespace problem_3505
}  // namespace leetcode
