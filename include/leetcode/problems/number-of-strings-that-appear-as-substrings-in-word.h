#include "leetcode/core.h"

namespace leetcode {
namespace problem_1967 {

using Func = std::function<int(std::vector<std::string>&, std::string)>;

class NumberOfStringsThatAppearAsSubstringsInWordSolution
    : public SolutionBase<Func> {
 public:
  //! 1967. Number of Strings That Appear as Substrings in Word
  //! https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/
  int numOfStrings(std::vector<std::string>& patterns, std::string word);

  NumberOfStringsThatAppearAsSubstringsInWordSolution();
};

}  // namespace problem_1967
}  // namespace leetcode
