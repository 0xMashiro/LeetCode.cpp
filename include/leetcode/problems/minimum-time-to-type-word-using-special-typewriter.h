#include "leetcode/core.h"

namespace leetcode {
namespace problem_1974 {

using Func = std::function<int(string)>;

class MinimumTimeToTypeWordUsingSpecialTypewriterSolution : public SolutionBase<Func> {
 public:
  //! 1974. Minimum Time to Type Word Using Special Typewriter
  //! https://leetcode.com/problems/minimum-time-to-type-word-using-special-typewriter/
  int minTimeToType(string word);

  MinimumTimeToTypeWordUsingSpecialTypewriterSolution();
};

}  // namespace problem_1974
}  // namespace leetcode
