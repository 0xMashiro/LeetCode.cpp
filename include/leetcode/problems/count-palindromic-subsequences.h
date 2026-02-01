
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2484 {

using Func = std::function<int(string)>;

class CountPalindromicSubsequencesSolution : public SolutionBase<Func> {
 public:
  int countPalindromes(string s);
  CountPalindromicSubsequencesSolution();
};

}  // namespace problem_2484
}  // namespace leetcode
