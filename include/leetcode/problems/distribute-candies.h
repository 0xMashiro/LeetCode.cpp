
#include "leetcode/core.h"

namespace leetcode {
namespace problem_575 {

using Func = std::function<int(vector<int>&)>;

class DistributeCandiesSolution : public SolutionBase<Func> {
 public:
  //! 575. Distribute Candies
  //! https://leetcode.com/problems/distribute-candies/
  int distributeCandies(vector<int>& candyType);

  DistributeCandiesSolution();
};

}  // namespace problem_575
}  // namespace leetcode
