#include "leetcode/core.h"

namespace leetcode {
namespace problem_2555 {

using Func = std::function<int(vector<int>&, int)>;

class MaximizeWinFromTwoSegmentsSolution : public SolutionBase<Func> {
 public:
  //! 2555. Maximize Win From Two Segments
  //! https://leetcode.com/problems/maximize-win-from-two-segments/
  int maximizeWin(vector<int>& prizePositions, int k);

  MaximizeWinFromTwoSegmentsSolution();
};

}  // namespace problem_2555
}  // namespace leetcode
