#include "leetcode/core.h"

namespace leetcode {
namespace problem_1106 {

using Func = std::function<bool(string)>;

class ParsingABooleanExpressionSolution : public SolutionBase<Func> {
 public:
  //! 1106. Parsing A Boolean Expression
  //! https://leetcode.com/problems/parsing-a-boolean-expression/
  bool parseBoolExpr(string expression);

  ParsingABooleanExpressionSolution();
};

}  // namespace problem_1106
}  // namespace leetcode
