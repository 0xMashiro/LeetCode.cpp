
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3047 {

using Func = std::function<long long(vector<vector<int>>&, vector<vector<int>>&)>;

class FindTheLargestAreaOfSquareInsideTwoRectanglesSolution : public SolutionBase<Func> {
 public:
  //! 3047. Find the Largest Area of Square Inside Two Rectangles
  //! https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/
  long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight);

  FindTheLargestAreaOfSquareInsideTwoRectanglesSolution();
};

}  // namespace problem_3047
}  // namespace leetcode