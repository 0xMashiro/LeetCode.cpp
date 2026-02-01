#include "leetcode/core.h"

namespace leetcode {
namespace problem_2895 {

using Func = std::function<int(vector<int>&, vector<int>&)>;

class MinimumProcessingTimeSolution : public SolutionBase<Func> {
 public:
  //! 2895. Minimum Processing Time
  //! https://leetcode.com/problems/minimum-processing-time/
  int minProcessingTime(vector<int>& processorTime, vector<int>& tasks);

  MinimumProcessingTimeSolution();
};

}  // namespace problem_2895
}  // namespace leetcode
