
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3258 {

using Func = std::function<int(string, int)>;

class CountSubstringsThatSatisfyKConstraintISolution : public SolutionBase<Func> {
 public:
  //! 3258. Count Substrings That Satisfy K-Constraint I
  //! https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-i/
  int countKConstraintSubstrings(string s, int k);

  CountSubstringsThatSatisfyKConstraintISolution();
};

}  // namespace problem_3258
}  // namespace leetcode
