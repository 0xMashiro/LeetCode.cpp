#include "leetcode/core.h"

namespace leetcode {
namespace problem_3007 {

using Func = std::function<long long(long long, int)>;

class MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKSolution : public SolutionBase<Func> {
 public:
  long long findMaximumNumber(long long k, int x);

  MaximumNumberThatSumOfThePricesIsLessThanOrEqualToKSolution();
};

}  // namespace problem_3007
}  // namespace leetcode
