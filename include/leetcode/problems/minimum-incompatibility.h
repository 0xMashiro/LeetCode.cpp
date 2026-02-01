
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1681 {

using Func = std::function<int(vector<int>&, int)>;

class MinimumIncompatibilitySolution : public SolutionBase<Func> {
 public:
  //! 1681. Minimum Incompatibility
  //! https://leetcode.com/problems/minimum-incompatibility/
  int minimumIncompatibility(vector<int>& nums, int k);

  MinimumIncompatibilitySolution();
};

}  // namespace problem_1681
}  // namespace leetcode
