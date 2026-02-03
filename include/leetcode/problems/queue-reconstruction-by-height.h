
#include "leetcode/core.h"

namespace leetcode {
namespace problem_406 {

using Func = std::function<vector<vector<int>>(vector<vector<int>>&)>;

class QueueReconstructionByHeightSolution : public SolutionBase<Func> {
 public:
  //! 406. Queue Reconstruction by Height
  //! https://leetcode.com/problems/queue-reconstruction-by-height/
  vector<vector<int>> reconstructQueue(vector<vector<int>>& people);

  QueueReconstructionByHeightSolution();
};

}  // namespace problem_406
}  // namespace leetcode
