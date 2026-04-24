#include "leetcode/core.h"

namespace leetcode {
namespace problem_2833 {

using Func = std::function<int(string&)>;

class FurthestPointFromOriginSolution : public SolutionBase<Func> {
 public:
  int furthestDistanceFromOrigin(string& moves);
  FurthestPointFromOriginSolution();
};

}  // namespace problem_2833
}  // namespace leetcode
