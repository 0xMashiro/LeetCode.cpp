#include "leetcode/core.h"

namespace leetcode {
namespace problem_29 {

using Func = std::function<int(int, int)>;

class DivideTwoIntegersSolution : public SolutionBase<Func> {
 public:
  //! 29. Divide Two Integers
  //! https://leetcode.com/problems/divide-two-integers/
  int divide(int dividend, int divisor);

  DivideTwoIntegersSolution();
};

}  // namespace problem_29
}  // namespace leetcode
