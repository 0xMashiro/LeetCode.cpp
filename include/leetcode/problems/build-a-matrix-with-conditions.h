#include "leetcode/core.h"

namespace leetcode {
namespace problem_2392 {

using Func = std::function<vector<vector<int>>(int, vector<vector<int>>&, vector<vector<int>>&)>;

class BuildAMatrixWithConditionsSolution : public SolutionBase<Func> {
 public:
  //! 2392. Build a Matrix With Conditions
  //! https://leetcode.com/problems/build-a-matrix-with-conditions/
  vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, 
                                   vector<vector<int>>& colConditions);

  BuildAMatrixWithConditionsSolution();
};

}  // namespace problem_2392
}  // namespace leetcode
