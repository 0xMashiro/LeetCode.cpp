#include "leetcode/core.h"

namespace leetcode {
namespace problem_2054 {

using Func = std::function<int(vector<vector<int>>&)>;

class TwoBestNonOverlappingEventsSolution : public SolutionBase<Func> {
 public:
  //! 2054. Two Best Non-Overlapping Events
  //! https://leetcode.com/problems/two-best-non-overlapping-events/
  int maxTwoEvents(vector<vector<int>>& events);

  TwoBestNonOverlappingEventsSolution();
};

}  // namespace problem_2054
}  // namespace leetcode