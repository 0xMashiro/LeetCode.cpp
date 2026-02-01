#include "leetcode/core.h"

namespace leetcode {
namespace problem_1297 {

using Func = std::function<int(string&, int, int, int)>;

/**
 * @brief 1297. Maximum Number of Occurrences of a Substring
 * @details Given a string s, return the maximum number of occurrences of 
 *          any substring under the following rules:
 *          - The number of unique characters in the substring must be <= maxLetters
 *          - The substring size must be between minSize and maxSize inclusive
 * @url https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/
 */
class MaximumNumberOfOccurrencesOfASubstringSolution : public SolutionBase<Func> {
 public:
  int maxFreq(string s, int maxLetters, int minSize, int maxSize);
  
  MaximumNumberOfOccurrencesOfASubstringSolution();
};

}  // namespace problem_1297
}  // namespace leetcode
