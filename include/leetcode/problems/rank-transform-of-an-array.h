#include "leetcode/core.h"

namespace leetcode {
namespace problem_1331 {

using Func = std::function<vector<int>(vector<int>&)>;

class RankTransformOfAnArraySolution : public SolutionBase<Func> {
 public:
  vector<int> arrayRankTransform(vector<int>& arr);

  RankTransformOfAnArraySolution();
};

}  // namespace problem_1331
}  // namespace leetcode