
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3722 {

using Func = std::function<string(string)>;

class LexicographicallySmallestStringAfterReverseSolution : public SolutionBase<Func> {
 public:
  //! 3722. Lexicographically Smallest String After Reverse
  //! https://leetcode.com/problems/lexicographically-smallest-string-after-reverse/
  string lexSmallest(string s);

  LexicographicallySmallestStringAfterReverseSolution();
};

}  // namespace problem_3722
}  // namespace leetcode
