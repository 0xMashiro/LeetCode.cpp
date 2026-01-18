
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1895 {

using Func = std::function<int(vector<vector<int>>&)>;

class LargestMagicSquareSolution : public SolutionBase<Func> {
 public:
  //! 1895. Largest Magic Square
  //! https://leetcode.com/problems/largest-magic-square/
  int largestMagicSquare(vector<vector<int>>& grid);

  LargestMagicSquareSolution();
};

}  // namespace problem_1895
}  // namespace leetcode
