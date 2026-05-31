#include "leetcode/core.h"

namespace leetcode {
namespace problem_2126 {

using Func = std::function<bool(int, std::vector<int>&)>;

class DestroyingAsteroidsSolution : public SolutionBase<Func> {
 public:
  //! 2126. Destroying Asteroids
  //! https://leetcode.com/problems/destroying-asteroids/
  bool asteroidsDestroyed(int mass, std::vector<int>& asteroids);

  DestroyingAsteroidsSolution();
};

}  // namespace problem_2126
}  // namespace leetcode
