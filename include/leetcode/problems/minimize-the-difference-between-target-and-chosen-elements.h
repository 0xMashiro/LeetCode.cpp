
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1981 {

using Func = std::function<int(vector<vector<int>>&, int)>;

class MinimizeTheDifferenceBetweenTargetAndChosenElementsSolution : public SolutionBase<Func> {
 public:
  //! 1981. Minimize the Difference Between Target and Chosen Elements
  //! https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/
  int minimizeTheDifference(vector<vector<int>>& mat, int target);

  MinimizeTheDifferenceBetweenTargetAndChosenElementsSolution();
};

}  // namespace problem_1981
}  // namespace leetcode
