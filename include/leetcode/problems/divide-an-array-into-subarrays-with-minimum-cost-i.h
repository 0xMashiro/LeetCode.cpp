#include "leetcode/core.h"

namespace leetcode {
namespace problem_3010 {

using Func = std::function<int(vector<int>&)>;

class DivideAnArrayIntoSubarraysWithMinimumCostISolution : public SolutionBase<Func> {
 public:
  int minimumCost(vector<int>& nums);

  DivideAnArrayIntoSubarraysWithMinimumCostISolution();
};

}  // namespace problem_3010
}  // namespace leetcode
