#include "leetcode/core.h"

namespace leetcode {
namespace problem_12 {

using Func = std::function<string(int)>;

class IntegerToRomanSolution : public SolutionBase<Func> {
 public:
  //! 12. Integer to Roman
  //! https://leetcode.com/problems/integer-to-roman/
  string intToRoman(int num);

  IntegerToRomanSolution();
};

}  // namespace problem_12
}  // namespace leetcode