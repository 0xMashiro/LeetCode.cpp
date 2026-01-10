#include "leetcode/core.h"

namespace leetcode {
namespace problem_712 {

using Func = std::function<int(string, string)>;

class MinimumAsciiDeleteSumForTwoStringsSolution : public SolutionBase<Func> {
 public:
  //! 712. Minimum ASCII Delete Sum for Two Strings
  //! https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
  int minimumDeleteSum(string s1, string s2);

  MinimumAsciiDeleteSumForTwoStringsSolution();
};

}  // namespace problem_712
}  // namespace leetcode