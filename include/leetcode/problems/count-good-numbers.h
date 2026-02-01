#include "leetcode/core.h"

namespace leetcode {
namespace problem_1922 {

using Func = std::function<int(long long)>;

/**
 * 1922. Count Good Numbers
 * https://leetcode.com/problems/count-good-numbers/
 * 
 * A digit string is good if the digits at even indices are even 
 * and the digits at odd indices are prime (2, 3, 5, or 7).
 * 
 * Return the total number of good digit strings of length n.
 * Since the answer may be large, return it modulo 10^9 + 7.
 */
class CountGoodNumbersSolution : public SolutionBase<Func> {
 public:
  //! 1922. Count Good Numbers
  //! https://leetcode.com/problems/count-good-numbers/
  int countGoodNumbers(long long n);

  CountGoodNumbersSolution();
};

}  // namespace problem_1922
}  // namespace leetcode
