#include "leetcode/core.h"

namespace leetcode {
namespace problem_3653 {

using Func = std::function<int(vector<int>&, vector<vector<int>>&)>;

class XorAfterRangeMultiplicationQueriesISolution : public SolutionBase<Func> {
 public:
  //! 3653. XOR After Range Multiplication Queries I
  //! https://leetcode.com/problems/xor-after-range-multiplication-queries-i/
  int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries);

  XorAfterRangeMultiplicationQueriesISolution();
};

}  // namespace problem_3653
}  // namespace leetcode
