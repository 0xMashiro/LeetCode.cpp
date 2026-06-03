#include "leetcode/core.h"

namespace leetcode {
namespace problem_3635 {

using Func = std::function<int(vector<int>&, vector<int>&, vector<int>&, vector<int>&)>;

class EarliestFinishTimeForLandAndWaterRidesIiSolution : public SolutionBase<Func> {
 public:
  int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                         vector<int>& waterStartTime, vector<int>& waterDuration);
  EarliestFinishTimeForLandAndWaterRidesIiSolution();
};

}  // namespace problem_3635
}  // namespace leetcode
