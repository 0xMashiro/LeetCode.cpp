#include "leetcode/core.h"

namespace leetcode {
namespace problem_1946 {

using Func = std::function<std::string(std::string&, std::vector<int>&)>;

class LargestNumberAfterMutatingSubstringSolution : public SolutionBase<Func> {
 public:
  //! 1946. Largest Number After Mutating Substring
  //! https://leetcode.com/problems/largest-number-after-mutating-substring/
  std::string maximumNumber(std::string num, std::vector<int>& change);

  LargestNumberAfterMutatingSubstringSolution();
};

}  // namespace problem_1946
}  // namespace leetcode
