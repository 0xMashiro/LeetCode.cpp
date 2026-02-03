#include "leetcode/core.h"

namespace leetcode {
namespace problem_71 {

using Func = std::function<string(string)>;

class SimplifyPathSolution : public SolutionBase<Func> {
 public:
  //! 71. Simplify Path
  //! https://leetcode.com/problems/simplify-path/
  string simplifyPath(string path);

  SimplifyPathSolution();
};

}  // namespace problem_71
}  // namespace leetcode
