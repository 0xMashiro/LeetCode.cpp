#include "leetcode/core.h"

namespace leetcode {
namespace problem_3536 {

using Func = std::function<int(int)>;

class MaximumProductOfTwoDigitsSolution : public SolutionBase<Func> {
 public:
  //! 3536. Maximum Product of Two Digits
  //! https://leetcode.com/problems/maximum-product-of-two-digits/
  int maxProduct(int n);

  MaximumProductOfTwoDigitsSolution();
};

}  // namespace problem_3536
}  // namespace leetcode
