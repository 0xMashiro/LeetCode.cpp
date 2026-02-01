
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1419 {

using Func = std::function<int(string)>;

class MinimumNumberOfFrogsCroakingSolution : public SolutionBase<Func> {
 public:
  //! 1419. Minimum Number of Frogs Croaking
  //! https://leetcode.com/problems/minimum-number-of-frogs-croaking/
  int minNumberOfFrogs(string croakOfFrogs);

  MinimumNumberOfFrogsCroakingSolution();
};

}  // namespace problem_1419
}  // namespace leetcode
