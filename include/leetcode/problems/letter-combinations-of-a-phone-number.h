
#include "leetcode/core.h"

namespace leetcode {
namespace problem_17 {

using Func = std::function<vector<string>(string)>;

class LetterCombinationsOfAPhoneNumberSolution : public SolutionBase<Func> {
 public:
  //! 17. Letter Combinations of a Phone Number
  //! https://leetcode.com/problems/letter-combinations-of-a-phone-number/
  vector<string> letterCombinations(string digits);

  LetterCombinationsOfAPhoneNumberSolution();
};

}  // namespace problem_17
}  // namespace leetcode
