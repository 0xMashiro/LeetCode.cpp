#include "leetcode/core.h"

namespace leetcode {
namespace problem_3789 {

using Func = std::function<long long(int, int, int, int, int)>;

class MinimumCostToAcquireRequiredItemsSolution : public SolutionBase<Func> {
 public:
  long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2);
  MinimumCostToAcquireRequiredItemsSolution();
};

}  // namespace problem_3789
}  // namespace leetcode
