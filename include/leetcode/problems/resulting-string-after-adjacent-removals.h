#include "leetcode/core.h"

namespace leetcode {
namespace problem_3561 {

using Func = std::function<string(string)>;

class ResultingStringAfterAdjacentRemovalsSolution : public SolutionBase<Func> {
 public:
  //! 3561. Resulting String After Adjacent Removals
  //! https://leetcode.com/problems/resulting-string-after-adjacent-removals/
  string resultingString(string s);

  ResultingStringAfterAdjacentRemovalsSolution();
};

}  // namespace problem_3561
}  // namespace leetcode
