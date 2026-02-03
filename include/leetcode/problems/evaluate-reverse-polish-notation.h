
#include "leetcode/core.h"

namespace leetcode {
namespace problem_150 {

using Func = std::function<int(vector<string>&)>;

class EvaluateReversePolishNotationSolution : public SolutionBase<Func> {
 public:
  //! 150. Evaluate Reverse Polish Notation
  //! https://leetcode.com/problems/evaluate-reverse-polish-notation/
  int evalRPN(vector<string>& tokens);

  EvaluateReversePolishNotationSolution();
};

}  // namespace problem_150
}  // namespace leetcode
