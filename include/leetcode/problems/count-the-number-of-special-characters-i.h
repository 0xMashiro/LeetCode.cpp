#include "leetcode/core.h"

namespace leetcode {
namespace problem_3120 {

using Func = std::function<int(string)>;

class CountTheNumberOfSpecialCharactersISolution : public SolutionBase<Func> {
 public:
  //! 3120. Count the Number of Special Characters I
  //! https://leetcode.com/problems/count-the-number-of-special-characters-i/
  int numberOfSpecialChars(string word);

  CountTheNumberOfSpecialCharactersISolution();
};

}  // namespace problem_3120
}  // namespace leetcode
