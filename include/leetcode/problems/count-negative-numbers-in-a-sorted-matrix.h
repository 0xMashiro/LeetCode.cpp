#include "leetcode/core.h"

namespace leetcode {
namespace problem_1351 {

using Func = std::function<int(vector<vector<int>>&)>;

class CountNegativeNumbersInASortedMatrixSolution : public SolutionBase<Func> {
 public:
  //! 1351. Count Negative Numbers in a Sorted Matrix
  //! https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/
  int countNegatives(vector<vector<int>>& grid);

  CountNegativeNumbersInASortedMatrixSolution();
};

}  // namespace problem_1351
}  // namespace leetcode