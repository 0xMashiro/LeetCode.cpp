#include "leetcode/core.h"

namespace leetcode {
namespace problem_1839 {

using Func = std::function<int(string)>;

class LongestSubstringOfAllVowelsInOrderSolution : public SolutionBase<Func> {
 public:
  //! 1839. Longest Substring Of All Vowels in Order
  //! https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/
  int longestBeautifulSubstring(string word);

  LongestSubstringOfAllVowelsInOrderSolution();
};

}  // namespace problem_1839
}  // namespace leetcode
