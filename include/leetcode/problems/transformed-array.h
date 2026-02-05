
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3379 {

using Func = std::function<vector<int>(vector<int>&)>;

class TransformedArraySolution : public SolutionBase<Func> {
 public:
  //! 3379. Transformed Array
  //! https://leetcode.com/problems/transformed-array/
  vector<int> constructTransformedArray(vector<int>& nums);

  TransformedArraySolution();
};

}  // namespace problem_3379
}  // namespace leetcode
