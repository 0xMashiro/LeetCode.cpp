
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3658 {

using Func = std::function<int(int)>;

class GcdOfOddAndEvenSumsSolution : public SolutionBase<Func> {
 public:
  //! 3658. GCD of Odd and Even Sums
  //! https://leetcode.com/problems/gcd-of-odd-and-even-sums/
  int gcdOfOddEvenSums(int n);

  GcdOfOddAndEvenSumsSolution();
};

}  // namespace problem_3658
}  // namespace leetcode
