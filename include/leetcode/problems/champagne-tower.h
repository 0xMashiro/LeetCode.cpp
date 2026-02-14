#include "leetcode/core.h"

namespace leetcode {
namespace problem_799 {

using Func = std::function<double(int, int, int)>;

class ChampagneTowerSolution : public SolutionBase<Func> {
 public:
  //! 799. Champagne Tower
  //! https://leetcode.com/problems/champagne-tower/
  double champagneTower(int poured, int query_row, int query_glass);

  ChampagneTowerSolution();
};

}  // namespace problem_799
}  // namespace leetcode
