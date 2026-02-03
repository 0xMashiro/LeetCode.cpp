
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2140 {

using Func = std::function<long long(vector<vector<int>>&)>;

class SolvingQuestionsWithBrainpowerSolution : public SolutionBase<Func> {
 public:
  //! 2140. Solving Questions With Brainpower
  //! https://leetcode.com/problems/solving-questions-with-brainpower/
  long long mostPoints(vector<vector<int>>& questions);

  SolvingQuestionsWithBrainpowerSolution();
};

}  // namespace problem_2140
}  // namespace leetcode
