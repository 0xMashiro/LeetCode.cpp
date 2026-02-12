#include "leetcode/core.h"

namespace leetcode {
namespace problem_3713 {

using Func = std::function<int(string)>;

class LongestBalancedSubstringISolution : public SolutionBase<Func> {
 public:
  //! 3713. Longest Balanced Substring I
  //! https://leetcode.com/problems/longest-balanced-substring-i/
  int longestBalanced(string s);

  LongestBalancedSubstringISolution();
};

}  // namespace problem_3713
}  // namespace leetcode
