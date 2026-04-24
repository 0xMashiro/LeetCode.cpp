#include "leetcode/core.h"

namespace leetcode {
namespace problem_231 {

using Func = std::function<bool(int)>;

class PowerOfTwoSolution : public SolutionBase<Func> {
 public:
  //! 231. Power of Two
  //! https://leetcode.com/problems/power-of-two/
  bool isPowerOfTwo(int n);

  PowerOfTwoSolution();
};

}  // namespace problem_231
}  // namespace leetcode
