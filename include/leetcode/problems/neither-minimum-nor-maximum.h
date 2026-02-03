#include "leetcode/core.h"

namespace leetcode {
namespace problem_2733 {

using Func = std::function<int(vector<int>&)>;

class NeitherMinimumNorMaximumSolution : public SolutionBase<Func> {
 public:
  int findNonMinOrMax(vector<int>& nums);
  NeitherMinimumNorMaximumSolution();
};

}  // namespace problem_2733
}  // namespace leetcode
