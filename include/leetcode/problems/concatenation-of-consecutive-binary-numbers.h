
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1680 {

using Func = std::function<int(int)>;

class ConcatenationOfConsecutiveBinaryNumbersSolution : public SolutionBase<Func> {
 public:
  //! 1680. Concatenation of Consecutive Binary Numbers
  //! https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/
  int concatenatedBinary(int n);

  ConcatenationOfConsecutiveBinaryNumbersSolution();
};

}  // namespace problem_1680
}  // namespace leetcode
