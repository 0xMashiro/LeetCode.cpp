#include "leetcode/core.h"

namespace leetcode {
namespace problem_365 {

using Func = std::function<bool(int, int, int)>;

class WaterAndJugProblemSolution : public SolutionBase<Func> {
 public:
  //! 365. Water and Jug Problem
  //! https://leetcode.com/problems/water-and-jug-problem/
  bool canMeasureWater(int x, int y, int target);

  WaterAndJugProblemSolution();
};

}  // namespace problem_365
}  // namespace leetcode
