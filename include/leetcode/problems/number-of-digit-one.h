#include "leetcode/core.h"

namespace leetcode {
namespace problem_233 {

using Func = std::function<int(int)>;

class NumberOfDigitOneSolution : public SolutionBase<Func> {
 public:
  //! 233. Number of Digit One
  //! https://leetcode.com/problems/number-of-digit-one/
  int countDigitOne(int n);

  NumberOfDigitOneSolution();
};

}  // namespace problem_233
}  // namespace leetcode
