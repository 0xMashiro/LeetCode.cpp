#include "leetcode/core.h"

namespace leetcode {
namespace problem_1417 {

using Func = std::function<std::string(std::string)>;

class ReformatTheStringSolution : public SolutionBase<Func> {
 public:
  //! 1417. Reformat The String
  //! https://leetcode.com/problems/reformat-the-string/
  std::string reformat(std::string s);

  ReformatTheStringSolution();
};

}  // namespace problem_1417
}  // namespace leetcode
