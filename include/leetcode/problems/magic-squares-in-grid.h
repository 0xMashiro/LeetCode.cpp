
#include "leetcode/core.h"

namespace leetcode {
namespace problem_840 {

using Func = std::function<int(vector<vector<int>>&)>;

class MagicSquaresInGridSolution : public SolutionBase<Func> {
 public:
  //! 840. Magic Squares In Grid
  //! https://leetcode.com/problems/magic-squares-in-grid/
  int numMagicSquaresInside(vector<vector<int>>& grid);

  MagicSquaresInGridSolution();
};

}  // namespace problem_840
}  // namespace leetcode