#include "leetcode/core.h"

namespace leetcode {
namespace problem_3362 {

using Func = std::function<int(vector<int>&, vector<vector<int>>&)>;

class ZeroArrayTransformationIiiSolution : public SolutionBase<Func> {
 public:
  //! 3362. Zero Array Transformation III
  //! https://leetcode.com/problems/zero-array-transformation-iii/
  int maxRemoval(vector<int>& nums, vector<vector<int>>& queries);

  ZeroArrayTransformationIiiSolution();
};

}  // namespace problem_3362
}  // namespace leetcode
