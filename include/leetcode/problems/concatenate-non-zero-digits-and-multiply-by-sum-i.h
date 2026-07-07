#include "leetcode/core.h"

namespace leetcode {
namespace problem_3754 {

using Func = std::function<long long(int)>;

class ConcatenateNonZeroDigitsAndMultiplyBySumISolution : public SolutionBase<Func> {
 public:
  //! 3754. Concatenate Non-Zero Digits and Multiply by Sum I
  //! https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/
  long long sumAndMultiply(int n);

  ConcatenateNonZeroDigitsAndMultiplyBySumISolution();
};

}  // namespace problem_3754
}  // namespace leetcode
