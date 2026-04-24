#include "leetcode/core.h"

namespace leetcode {
namespace problem_1799 {

using Func = std::function<int(vector<int>&)>;

class MaximizeScoreAfterNOperationsSolution : public SolutionBase<Func> {
 public:
  int maxScore(vector<int>& nums);
  MaximizeScoreAfterNOperationsSolution();
};

}  // namespace problem_1799
}  // namespace leetcode
