#include "leetcode/core.h"

namespace leetcode {
namespace problem_3629 {

using Func = std::function<int(vector<int>&)>;

class MinimumJumpsToReachEndViaPrimeTeleportationSolution : public SolutionBase<Func> {
 public:
  int minJumps(vector<int>& nums);
  MinimumJumpsToReachEndViaPrimeTeleportationSolution();
};

}  // namespace problem_3629
}  // namespace leetcode
