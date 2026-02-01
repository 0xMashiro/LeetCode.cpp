#include "leetcode/core.h"

namespace leetcode {
namespace problem_191 {

using Func = std::function<int(int)>;

class NumberOf1BitsSolution : public SolutionBase<Func> {
 public:
  //! 191. Number of 1 Bits
  //! https://leetcode.com/problems/number-of-1-bits/
  int hammingWeight(int n);

  NumberOf1BitsSolution();
};

}  // namespace problem_191
}  // namespace leetcode
