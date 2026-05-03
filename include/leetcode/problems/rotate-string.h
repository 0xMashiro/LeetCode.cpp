#include "leetcode/core.h"

namespace leetcode {
namespace problem_796 {

using Func = std::function<bool(string, string)>;

class RotateStringSolution : public SolutionBase<Func> {
 public:
  //! 796. Rotate String
  //! https://leetcode.com/problems/rotate-string/
  bool rotateString(string s, string goal);

  RotateStringSolution();
};

}  // namespace problem_796
}  // namespace leetcode
