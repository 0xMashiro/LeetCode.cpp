#include "leetcode/core.h"

namespace leetcode {
namespace problem_3314 {

using Func = std::function<std::vector<int>(std::vector<int>&)>;

class ConstructTheMinimumBitwiseArrayISolution : public SolutionBase<Func> {
 public:
  //! 3314. Construct the Minimum Bitwise Array I
  //! https://leetcode.com/problems/construct-the-minimum-bitwise-array-i/
  std::vector<int> minBitwiseArray(std::vector<int>& nums);

  ConstructTheMinimumBitwiseArrayISolution();
};

}  // namespace problem_3314
}  // namespace leetcode