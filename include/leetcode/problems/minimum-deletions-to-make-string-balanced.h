#include "leetcode/core.h"

namespace leetcode {
namespace problem_1653 {

using Func = std::function<int(string)>;

class MinimumDeletionsToMakeStringBalancedSolution : public SolutionBase<Func> {
 public:
  int minimumDeletions(string s);

  MinimumDeletionsToMakeStringBalancedSolution();
};

}  // namespace problem_1653
}  // namespace leetcode
