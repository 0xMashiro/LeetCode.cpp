#include "leetcode/core.h"

namespace leetcode {
namespace problem_730 {

using Func = std::function<int(string)>;

class CountDifferentPalindromicSubsequencesSolution : public SolutionBase<Func> {
 public:
  //! 730. Count Different Palindromic Subsequences
  //! https://leetcode.com/problems/count-different-palindromic-subsequences/
  int countPalindromicSubsequences(string s);

  CountDifferentPalindromicSubsequencesSolution();
};

}  // namespace problem_730
}  // namespace leetcode
