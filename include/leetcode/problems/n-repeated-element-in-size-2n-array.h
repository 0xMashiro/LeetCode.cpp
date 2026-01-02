#include "leetcode/core.h"

namespace leetcode {
namespace problem_961 {

using Func = std::function<int(vector<int>&)>;

class NRepeatedElementInSize2nArraySolution : public SolutionBase<Func> {
 public:
  //! 961. N-Repeated Element in Size 2N Array
  //! https://leetcode.com/problems/n-repeated-element-in-size-2n-array/
  int repeatedNTimes(vector<int>& nums);

  NRepeatedElementInSize2nArraySolution();
};

}  // namespace problem_961
}  // namespace leetcode