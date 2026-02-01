#include "leetcode/core.h"

namespace leetcode {
namespace problem_1626 {

using Func = std::function<int(vector<int>&, vector<int>&)>;

class BestTeamWithNoConflictsSolution : public SolutionBase<Func> {
 public:
  int bestTeamScore(vector<int>& scores, vector<int>& ages);

  BestTeamWithNoConflictsSolution();
};

}  // namespace problem_1626
}  // namespace leetcode