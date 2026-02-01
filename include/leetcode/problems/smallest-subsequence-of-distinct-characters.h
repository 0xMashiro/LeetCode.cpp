#include "leetcode/core.h"

namespace leetcode {
namespace problem_1081 {

using Func = std::function<string(string)>;

class SmallestSubsequenceOfDistinctCharactersSolution : public SolutionBase<Func> {
 public:
  //! 1081. Smallest Subsequence of Distinct Characters
  //! https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/
  string smallestSubsequence(string s);

  SmallestSubsequenceOfDistinctCharactersSolution();
};

}  // namespace problem_1081
}  // namespace leetcode
