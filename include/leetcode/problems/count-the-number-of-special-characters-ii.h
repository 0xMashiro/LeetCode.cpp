#include "leetcode/core.h"

namespace leetcode {
namespace problem_3121 {

using Func = std::function<int(std::string)>;

class CountTheNumberOfSpecialCharactersIiSolution : public SolutionBase<Func> {
 public:
  //! 3121. Count the Number of Special Characters II
  //! https://leetcode.com/problems/count-the-number-of-special-characters-ii/
  int numberOfSpecialChars(std::string word);

  CountTheNumberOfSpecialCharactersIiSolution();
};

}  // namespace problem_3121
}  // namespace leetcode
