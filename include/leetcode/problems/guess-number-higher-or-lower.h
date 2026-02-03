
#include "leetcode/core.h"

namespace leetcode {
namespace problem_374 {

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return       -1 if num is higher than the picked number
 *                1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

using Func = std::function<int(int)>;

class GuessNumberHigherOrLowerSolution : public SolutionBase<Func> {
 public:
  //! 374. Guess Number Higher or Lower
  //! https://leetcode.com/problems/guess-number-higher-or-lower/
  int guessNumber(int n);

  GuessNumberHigherOrLowerSolution();
};

}  // namespace problem_374
}  // namespace leetcode
