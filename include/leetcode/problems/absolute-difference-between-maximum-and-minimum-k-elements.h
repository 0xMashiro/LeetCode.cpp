
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3774 {

using Func = std::function<int(vector<int>&, int)>;

class AbsoluteDifferenceBetweenMaximumAndMinimumKElementsSolution : public SolutionBase<Func> {
 public:
  int absDifference(vector<int>& nums, int k);

  AbsoluteDifferenceBetweenMaximumAndMinimumKElementsSolution();
};

}  // namespace problem_3774
}  // namespace leetcode
