#include "leetcode/core.h"

namespace leetcode {
namespace problem_3633 {

using Func = std::function<int(vector<int>&, vector<int>&, vector<int>&, vector<int>&)>;

class EarliestFinishTimeForLandAndWaterRidesISolution : public SolutionBase<Func> {
 public:
  int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                         vector<int>& waterStartTime, vector<int>& waterDuration);
  EarliestFinishTimeForLandAndWaterRidesISolution();
};

}  // namespace problem_3633
}  // namespace leetcode
