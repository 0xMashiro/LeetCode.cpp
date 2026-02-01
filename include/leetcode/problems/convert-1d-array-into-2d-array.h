
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2022 {

using Func = std::function<vector<vector<int>>(vector<int>&, int, int)>;

class Convert1dArrayInto2dArraySolution : public SolutionBase<Func> {
 public:
  //! 2022. Convert 1D Array Into 2D Array
  //! https://leetcode.com/problems/convert-1d-array-into-2d-array/
  vector<vector<int>> construct2DArray(vector<int>& original, int m, int n);

  Convert1dArrayInto2dArraySolution();
};

}  // namespace problem_2022
}  // namespace leetcode
