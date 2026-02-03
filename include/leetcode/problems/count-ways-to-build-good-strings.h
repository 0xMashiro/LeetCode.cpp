#include "leetcode/core.h"

namespace leetcode {
namespace problem_2466 {

using Func = std::function<int(int, int, int, int)>;

class CountWaysToBuildGoodStringsSolution : public SolutionBase<Func> {
 public:
  //! 2466. Count Ways To Build Good Strings
  //! https://leetcode.com/problems/count-ways-to-build-good-strings/
  int countGoodStrings(int low, int high, int zero, int one);

  CountWaysToBuildGoodStringsSolution();
};

}  // namespace problem_2466
}  // namespace leetcode
