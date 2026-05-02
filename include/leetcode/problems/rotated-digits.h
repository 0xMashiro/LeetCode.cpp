#include "leetcode/core.h"

namespace leetcode {
namespace problem_788 {

using Func = std::function<int(int)>;

class RotatedDigitsSolution : public SolutionBase<Func> {
 public:
  int rotatedDigits(int n);
  RotatedDigitsSolution();
};

}  // namespace problem_788
}  // namespace leetcode
