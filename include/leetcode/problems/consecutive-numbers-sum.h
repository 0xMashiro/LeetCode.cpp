#include "leetcode/core.h"

namespace leetcode {
namespace problem_829 {

using Func = std::function<int(int)>;

class ConsecutiveNumbersSumSolution : public SolutionBase<Func> {
 public:
  //! 829. Consecutive Numbers Sum
  //! https://leetcode.com/problems/consecutive-numbers-sum/
  int consecutiveNumbersSum(int n);

  ConsecutiveNumbersSumSolution();
};

}  // namespace problem_829
}  // namespace leetcode
