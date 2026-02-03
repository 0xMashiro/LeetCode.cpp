
#include "leetcode/core.h"

namespace leetcode {
namespace problem_456 {

using Func = std::function<bool(vector<int>&)>;

class Pattern132Solution : public SolutionBase<Func> {
 public:
  //! 456. 132 Pattern
  //! https://leetcode.com/problems/132-pattern/
  bool find132pattern(vector<int>& nums);

  Pattern132Solution();
};

}  // namespace problem_456
}  // namespace leetcode
