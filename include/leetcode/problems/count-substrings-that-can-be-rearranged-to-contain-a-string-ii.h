
#include "leetcode/core.h"

namespace leetcode {
namespace problem_3298 {

using Func = std::function<long long(const string&, const string&)>;

/**
 * Count Substrings That Can Be Rearranged to Contain a String II
 * https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/
 * 
 * A substring is valid if it can be rearranged to have word2 as a prefix.
 * This means the substring must contain at least as many of each character as word2.
 */
class CountSubstringsThatCanBeRearrangedToContainAStringIiSolution : public SolutionBase<Func> {
 public:
  long long validSubstringCount(const string& word1, const string& word2);

  CountSubstringsThatCanBeRearrangedToContainAStringIiSolution();
};

}  // namespace problem_3298
}  // namespace leetcode
