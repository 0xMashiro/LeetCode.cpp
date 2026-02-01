#include "leetcode/core.h"

namespace leetcode {
namespace problem_20 {

using Func = std::function<bool(std::string)>;

class ValidParenthesesSolution : public SolutionBase<Func> {
 public:
  //! 20. Valid Parentheses
  //! https://leetcode.com/problems/valid-parentheses/
  bool isValid(std::string s);

  ValidParenthesesSolution();
};

}  // namespace problem_20
}  // namespace leetcode
