#include "leetcode/core.h"

namespace leetcode {
namespace problem_1970 {

using Func = std::function<int(int, int, vector<vector<int>>&)>;

class LastDayWhereYouCanStillCrossSolution : public SolutionBase<Func> {
 public:
  //! 1970. Last Day Where You Can Still Cross
  //! https://leetcode.com/problems/last-day-where-you-can-still-cross/
  int latestDayToCross(int row, int col, vector<vector<int>>& cells);

  LastDayWhereYouCanStillCrossSolution();
};

}  // namespace problem_1970
}  // namespace leetcode