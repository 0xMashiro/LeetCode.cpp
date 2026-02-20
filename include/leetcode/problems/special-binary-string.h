#include "leetcode/core.h"

namespace leetcode {
namespace problem_761 {

using Func = std::function<string(string)>;

class SpecialBinaryStringSolution : public SolutionBase<Func> {
 public:
  //! 761. Special Binary String
  //! https://leetcode.com/problems/special-binary-string/
  string makeLargestSpecial(string s);

  SpecialBinaryStringSolution();
};

}  // namespace problem_761
}  // namespace leetcode
