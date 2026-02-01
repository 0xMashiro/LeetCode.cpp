
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3791 {

using Func = std::function<long long(long long, long long)>;

class NumberOfBalancedIntegersInARangeSolution : public SolutionBase<Func> {
 public:
  //! 3791. Number of Balanced Integers in a Range
  //! https://leetcode.com/problems/number-of-balanced-integers-in-a-range/
  long long countBalanced(long long low, long long high);

  NumberOfBalancedIntegersInARangeSolution();
};

}  // namespace problem_3791
}  // namespace leetcode
