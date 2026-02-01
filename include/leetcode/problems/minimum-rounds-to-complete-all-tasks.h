
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2244 {

using Func = std::function<int(vector<int>&)>;

class MinimumRoundsToCompleteAllTasksSolution : public SolutionBase<Func> {
 public:
  //! 2244. Minimum Rounds to Complete All Tasks
  //! https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/
  int minimumRounds(vector<int>& tasks);

  MinimumRoundsToCompleteAllTasksSolution();
};

}  // namespace problem_2244
}  // namespace leetcode
