
#include "leetcode/core.h"

namespace leetcode {
namespace problem_132 {

using Func = std::function<int(string)>;

class PalindromePartitioningIiSolution : public SolutionBase<Func> {
 public:
  //! 132. Palindrome Partitioning II
  //! https://leetcode.com/problems/palindrome-partitioning-ii/
  int minCut(string s);

  PalindromePartitioningIiSolution();
};

}  // namespace problem_132
}  // namespace leetcode
