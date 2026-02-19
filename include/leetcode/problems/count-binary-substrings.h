
#include "leetcode/core.h"

namespace leetcode {
namespace problem_696 {

using Func = std::function<int(string)>;

class CountBinarySubstringsSolution : public SolutionBase<Func> {
 public:
  //! 696. Count Binary Substrings
  //! https://leetcode.com/problems/count-binary-substrings/
  int countBinarySubstrings(string s);

  CountBinarySubstringsSolution();
};

}  // namespace problem_696
}  // namespace leetcode
