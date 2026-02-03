#include "leetcode/core.h"

namespace leetcode {
namespace problem_2335 {

using Func = std::function<int(vector<int>&)>;

class MinimumAmountOfTimeToFillCupsSolution : public SolutionBase<Func> {
 public:
  //! 2335. Minimum Amount of Time to Fill Cups
  //! https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/
  int fillCups(vector<int>& amount);

  MinimumAmountOfTimeToFillCupsSolution();
};

}  // namespace problem_2335
}  // namespace leetcode