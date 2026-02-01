#include "leetcode/core.h"

namespace leetcode {
namespace problem_2014 {

using Func = std::function<std::string(const std::string&, int)>;

class LongestSubsequenceRepeatedKTimesSolution : public SolutionBase<Func> {
 public:
  //! 2014. Longest Subsequence Repeated k Times
  //! https://leetcode.com/problems/longest-subsequence-repeated-k-times/
  std::string longestSubsequenceRepeatedK(const std::string& s, int k);

  LongestSubsequenceRepeatedKTimesSolution();
};

}  // namespace problem_2014
}  // namespace leetcode
