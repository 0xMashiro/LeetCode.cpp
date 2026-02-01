#include "leetcode/core.h"

namespace leetcode {
namespace problem_1544 {

using Func = std::function<std::string(std::string)>;

class MakeTheStringGreatSolution : public SolutionBase<Func> {
 public:
  //! 1544. Make The String Great
  //! https://leetcode.com/problems/make-the-string-great/
  std::string makeGood(std::string s);

  MakeTheStringGreatSolution();
};

}  // namespace problem_1544
}  // namespace leetcode
