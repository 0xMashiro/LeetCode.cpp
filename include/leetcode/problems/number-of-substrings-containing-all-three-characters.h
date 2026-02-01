#include "leetcode/core.h"

namespace leetcode {
namespace problem_1358 {

using Func = std::function<int(string)>;

class NumberOfSubstringsContainingAllThreeCharactersSolution : public SolutionBase<Func> {
 public:
  //! 1358. Number of Substrings Containing All Three Characters
  //! https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/
  int numberOfSubstrings(string s);

  NumberOfSubstringsContainingAllThreeCharactersSolution();
};

}  // namespace problem_1358
}  // namespace leetcode
