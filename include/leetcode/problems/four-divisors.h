#include "leetcode/core.h"

namespace leetcode {
namespace problem_1390 {

using Func = std::function<int(vector<int>&)>;

class FourDivisorsSolution : public SolutionBase<Func> {
 public:
  //! 1390. Four Divisors
  //! https://leetcode.com/problems/four-divisors/
  int sumFourDivisors(vector<int>& nums);

  FourDivisorsSolution();
};

}  // namespace problem_1390
}  // namespace leetcode