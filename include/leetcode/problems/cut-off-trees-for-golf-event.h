#include "leetcode/core.h"

namespace leetcode {
namespace problem_675 {

using Func = std::function<int(vector<vector<int>> &)>;

class CutOffTreesForGolfEventSolution : public SolutionBase<Func> {
 public:
  //! 675. Cut Off Trees for Golf Event
  //! https://leetcode.com/problems/cut-off-trees-for-golf-event/
  int cutOffTree(vector<vector<int>> &forest);

  CutOffTreesForGolfEventSolution();
};

}  // namespace problem_675
}  // namespace leetcode
