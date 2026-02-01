#include "leetcode/core.h"

namespace leetcode {
namespace problem_2712 {

using Func = std::function<long long(string)>;

class MinimumCostToMakeAllCharactersEqualSolution : public SolutionBase<Func> {
 public:
  //! 2712. Minimum Cost to Make All Characters Equal
  //! https://leetcode.com/problems/minimum-cost-to-make-all-characters-equal/
  long long minimumCost(string s);

  MinimumCostToMakeAllCharactersEqualSolution();
};

}  // namespace problem_2712
}  // namespace leetcode
