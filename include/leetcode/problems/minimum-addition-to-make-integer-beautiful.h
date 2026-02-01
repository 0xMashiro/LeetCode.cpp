#include "leetcode/core.h"

namespace leetcode {
namespace problem_2457 {

using Func = std::function<long long(long long, int)>;

class MinimumAdditionToMakeIntegerBeautifulSolution : public SolutionBase<Func> {
 public:
  //! 2457. Minimum Addition to Make Integer Beautiful
  //! https://leetcode.com/problems/minimum-addition-to-make-integer-beautiful/
  long long makeIntegerBeautiful(long long n, int target);

  MinimumAdditionToMakeIntegerBeautifulSolution();
};

}  // namespace problem_2457
}  // namespace leetcode
