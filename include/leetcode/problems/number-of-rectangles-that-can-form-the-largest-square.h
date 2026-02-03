#include "leetcode/core.h"

namespace leetcode {
namespace problem_1725 {

using Func = std::function<int(vector<vector<int>>&)>;

class NumberOfRectanglesThatCanFormTheLargestSquareSolution : public SolutionBase<Func> {
 public:
  //! 1725. Number Of Rectangles That Can Form The Largest Square
  //! https://leetcode.com/problems/number-of-rectangles-that-can-form-the-largest-square/
  int countGoodRectangles(vector<vector<int>>& rectangles);

  NumberOfRectanglesThatCanFormTheLargestSquareSolution();
};

}  // namespace problem_1725
}  // namespace leetcode
