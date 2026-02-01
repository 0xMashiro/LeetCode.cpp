#include "leetcode/core.h"

namespace leetcode {
namespace problem_3290 {

using Func = std::function<long long(vector<int>&, vector<int>&)>;

class MaximumMultiplicationScoreSolution : public SolutionBase<Func> {
 public:
  long long maxScore(vector<int>& a, vector<int>& b);

  MaximumMultiplicationScoreSolution();
};

}  // namespace problem_3290
}  // namespace leetcode
