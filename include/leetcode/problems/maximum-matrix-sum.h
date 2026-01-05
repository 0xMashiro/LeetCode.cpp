#include "leetcode/core.h"

namespace leetcode {
namespace problem_1975 {

using Func = std::function<long long(vector<vector<int>>&)>;

class MaximumMatrixSumSolution : public SolutionBase<Func> {
 public:
  //! 1975. Maximum Matrix Sum
  //! https://leetcode.com/problems/maximum-matrix-sum/
  long long maxMatrixSum(vector<vector<int>>& matrix);

  MaximumMatrixSumSolution();
};

}  // namespace problem_1975
}  // namespace leetcode