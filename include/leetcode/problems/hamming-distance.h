#include "leetcode/core.h"

namespace leetcode {
namespace problem_461 {

using Func = std::function<int(int, int)>;

class HammingDistanceSolution : public SolutionBase<Func> {
 public:
  //! 461. Hamming Distance
  //! https://leetcode.com/problems/hamming-distance/
  int hammingDistance(int x, int y);

  HammingDistanceSolution();
};

}  // namespace problem_461
}  // namespace leetcode
