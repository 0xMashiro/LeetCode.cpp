
#include "leetcode/core.h"

namespace leetcode {
namespace problem_744 {

using Func = std::function<char(std::vector<char>&, char)>;

class FindSmallestLetterGreaterThanTargetSolution : public SolutionBase<Func> {
 public:
  //! 744. Find Smallest Letter Greater Than Target
  //! https://leetcode.com/problems/find-smallest-letter-greater-than-target/
  char nextGreatestLetter(std::vector<char>& letters, char target);

  FindSmallestLetterGreaterThanTargetSolution();
};

}  // namespace problem_744
}  // namespace leetcode