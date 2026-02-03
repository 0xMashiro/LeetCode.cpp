#include "leetcode/core.h"

namespace leetcode {
namespace problem_459 {

using Func = std::function<bool(string)>;

class RepeatedSubstringPatternSolution : public SolutionBase<Func> {
 public:
  //! 459. Repeated Substring Pattern
  //! https://leetcode.com/problems/repeated-substring-pattern/
  bool repeatedSubstringPattern(string s);

  RepeatedSubstringPatternSolution();
};

}  // namespace problem_459
}  // namespace leetcode
