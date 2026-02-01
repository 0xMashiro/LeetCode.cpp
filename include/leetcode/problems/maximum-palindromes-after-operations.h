#include "leetcode/core.h"

namespace leetcode {
namespace problem_3035 {

using Func = std::function<int(vector<string>&)>;

class MaximumPalindromesAfterOperationsSolution : public SolutionBase<Func> {
 public:
  //! 3035. Maximum Palindromes After Operations
  //! https://leetcode.com/problems/maximum-palindromes-after-operations/
  int maxPalindromesAfterOperations(vector<string>& words);

  MaximumPalindromesAfterOperationsSolution();
};

}  // namespace problem_3035
}  // namespace leetcode
