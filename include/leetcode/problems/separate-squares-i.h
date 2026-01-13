#include "leetcode/core.h"

namespace leetcode {
namespace problem_3453 {

using Func = std::function<double(vector<vector<int>>&)>;

class SeparateSquaresISolution : public SolutionBase<Func> {
 public:
  //! 3453. Separate Squares I
  //! https://leetcode.com/problems/separate-squares-i/
  double separateSquares(vector<vector<int>>& squares);

  SeparateSquaresISolution();
};

}  // namespace problem_3453
}  // namespace leetcode