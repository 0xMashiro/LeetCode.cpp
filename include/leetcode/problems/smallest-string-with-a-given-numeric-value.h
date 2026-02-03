#include "leetcode/core.h"

namespace leetcode {
namespace problem_1663 {

using Func = std::function<string(int, int)>;

class SmallestStringWithAGivenNumericValueSolution : public SolutionBase<Func> {
 public:
  //! 1663. Smallest String With A Given Numeric Value
  //! https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/
  string getSmallestString(int n, int k);

  SmallestStringWithAGivenNumericValueSolution();
};

}  // namespace problem_1663
}  // namespace leetcode
