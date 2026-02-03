#include "leetcode/core.h"

namespace leetcode {
namespace problem_371 {

using Func = std::function<int(int, int)>;

class SumOfTwoIntegersSolution : public SolutionBase<Func> {
 public:
  //! 371. Sum of Two Integers
  //! https://leetcode.com/problems/sum-of-two-integers/
  int getSum(int a, int b);

  SumOfTwoIntegersSolution();
};

}  // namespace problem_371
}  // namespace leetcode
