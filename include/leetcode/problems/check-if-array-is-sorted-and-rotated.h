#include "leetcode/core.h"

namespace leetcode {
namespace problem_1752 {

using Func = std::function<bool(vector<int>&)>;

class CheckIfArrayIsSortedAndRotatedSolution : public SolutionBase<Func> {
 public:
  bool check(vector<int>& nums);
  CheckIfArrayIsSortedAndRotatedSolution();
};

}  // namespace problem_1752
}  // namespace leetcode
