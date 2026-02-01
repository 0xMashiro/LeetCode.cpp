#include "leetcode/core.h"

namespace leetcode {
namespace problem_1593 {

using Func = std::function<int(string)>;

class SplitAStringIntoTheMaxNumberOfUniqueSubstringsSolution : public SolutionBase<Func> {
 public:
  //! 1593. Split a String Into the Max Number of Unique Substrings
  //! https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/
  int maxUniqueSplit(string s);

  SplitAStringIntoTheMaxNumberOfUniqueSubstringsSolution();
};

}  // namespace problem_1593
}  // namespace leetcode
