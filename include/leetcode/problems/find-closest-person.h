#include "leetcode/core.h"

namespace leetcode {
namespace problem_3516 {

using Func = std::function<int(int, int, int)>;

class FindClosestPersonSolution : public SolutionBase<Func> {
 public:
  //! 3516. Find Closest Person
  //! https://leetcode.com/problems/find-closest-person/
  int findClosest(int x, int y, int z);

  FindClosestPersonSolution();
};

}  // namespace problem_3516
}  // namespace leetcode
