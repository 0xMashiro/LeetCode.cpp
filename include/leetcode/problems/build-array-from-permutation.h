
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1920 {

using Func = std::function<vector<int>(vector<int>&)>;

class BuildArrayFromPermutationSolution : public SolutionBase<Func> {
 public:
  //! 1920. Build Array from Permutation
  //! https://leetcode.com/problems/build-array-from-permutation/
  vector<int> buildArray(vector<int>& nums);

  BuildArrayFromPermutationSolution();
};

}  // namespace problem_1920
}  // namespace leetcode
