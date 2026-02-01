#include "leetcode/core.h"

namespace leetcode {
namespace problem_2530 {

using Func = std::function<long long(vector<int>&, int)>;

class MaximalScoreAfterApplyingKOperationsSolution : public SolutionBase<Func> {
 public:
  long long maxKelements(vector<int>& nums, int k);

  MaximalScoreAfterApplyingKOperationsSolution();
};

}  // namespace problem_2530
}  // namespace leetcode