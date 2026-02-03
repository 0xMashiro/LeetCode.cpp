#include "leetcode/core.h"

namespace leetcode {
namespace problem_2786 {

using Func = std::function<long long(vector<int>&, int)>;

class VisitArrayPositionsToMaximizeScoreSolution : public SolutionBase<Func> {
 public:
  //! 2786. Visit Array Positions to Maximize Score
  //! https://leetcode.com/problems/visit-array-positions-to-maximize-score/
  long long maxScore(vector<int>& nums, int x);

  VisitArrayPositionsToMaximizeScoreSolution();
};

}  // namespace problem_2786
}  // namespace leetcode
