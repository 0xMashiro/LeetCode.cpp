#include "leetcode/core.h"

namespace leetcode {
namespace problem_2744 {

using Func = std::function<int(vector<string>&)>;

class FindMaximumNumberOfStringPairsSolution : public SolutionBase<Func> {
 public:
  //! 2744. Find Maximum Number of String Pairs
  //! https://leetcode.com/problems/find-maximum-number-of-string-pairs/
  int maximumNumberOfStringPairs(vector<string>& words);

  FindMaximumNumberOfStringPairsSolution();
};

}  // namespace problem_2744
}  // namespace leetcode
