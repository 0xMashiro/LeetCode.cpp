#include "leetcode/core.h"

namespace leetcode {
namespace problem_3498 {

using Func = std::function<int(string)>;

class ReverseDegreeOfAStringSolution : public SolutionBase<Func> {
 public:
  //! 3498. Reverse Degree of a String
  //! https://leetcode.com/problems/reverse-degree-of-a-string/
  int reverseDegree(string s);

  ReverseDegreeOfAStringSolution();
};

}  // namespace problem_3498
}  // namespace leetcode
