#include "leetcode/core.h"

namespace leetcode {
namespace problem_3350 {

using Func = std::function<int(vector<int>&)>;

class AdjacentIncreasingSubarraysDetectionIiSolution : public SolutionBase<Func> {
 public:
  //! 3350. Adjacent Increasing Subarrays Detection II
  //! https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/
  int maxIncreasingSubarrays(vector<int>& nums);

  AdjacentIncreasingSubarraysDetectionIiSolution();
};

}  // namespace problem_3350
}  // namespace leetcode
