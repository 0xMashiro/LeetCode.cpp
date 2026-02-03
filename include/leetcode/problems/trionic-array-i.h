#include "leetcode/core.h"

namespace leetcode {
namespace problem_3637 {

using Func = std::function<bool(vector<int>&)>;

class TrionicArrayISolution : public SolutionBase<Func> {
 public:
  //! 3637. Trionic Array I
  //! https://leetcode.com/problems/trionic-array-i/
  bool isTrionic(vector<int>& nums);

  TrionicArrayISolution();
};

}  // namespace problem_3637
}  // namespace leetcode