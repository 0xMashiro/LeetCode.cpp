#include "leetcode/core.h"

namespace leetcode {
namespace problem_2913 {

using Func = std::function<int(vector<int>&)>;

class SubarraysDistinctElementSumOfSquaresISolution : public SolutionBase<Func> {
 public:
  //! 2913. Subarrays Distinct Element Sum of Squares I
  //! https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/
  int sumCounts(vector<int>& nums);

  SubarraysDistinctElementSumOfSquaresISolution();
};

}  // namespace problem_2913
}  // namespace leetcode
