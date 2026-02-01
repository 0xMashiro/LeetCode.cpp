#include "leetcode/core.h"

namespace leetcode {
namespace problem_740 {

using Func = std::function<int(vector<int>&)>;

class DeleteAndEarnSolution : public SolutionBase<Func> {
 public:
  //! 740. Delete and Earn
  //! https://leetcode.com/problems/delete-and-earn/
  int deleteAndEarn(vector<int>& nums);

  DeleteAndEarnSolution();
};

}  // namespace problem_740
}  // namespace leetcode
