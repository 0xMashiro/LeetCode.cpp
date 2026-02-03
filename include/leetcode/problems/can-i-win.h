#include "leetcode/core.h"

namespace leetcode {
namespace problem_464 {

using Func = std::function<bool(int, int)>;

class CanIWinSolution : public SolutionBase<Func> {
 public:
  //! 464. Can I Win
  //! https://leetcode.com/problems/can-i-win/
  bool canIWin(int maxChoosableInteger, int desiredTotal);

  CanIWinSolution();
};

}  // namespace problem_464
}  // namespace leetcode
