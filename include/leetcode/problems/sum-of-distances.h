#include "leetcode/core.h"

namespace leetcode {
namespace problem_2615 {

using Func = std::function<vector<long long>(vector<int>&)>;

class SumOfDistancesSolution : public SolutionBase<Func> {
 public:
  //! 2615. Sum of Distances
  //! https://leetcode.com/problems/sum-of-distances/
  vector<long long> distance(vector<int>& nums);

  SumOfDistancesSolution();
};

}  // namespace problem_2615
}  // namespace leetcode
