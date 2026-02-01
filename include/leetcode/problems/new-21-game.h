#include "leetcode/core.h"

namespace leetcode {
namespace problem_837 {

using Func = std::function<double(int, int, int)>;

class New21GameSolution : public SolutionBase<Func> {
 public:
  //! 837. New 21 Game
  //! https://leetcode.com/problems/new-21-game/
  double new21Game(int n, int k, int maxPts);

  New21GameSolution();
};

}  // namespace problem_837
}  // namespace leetcode
