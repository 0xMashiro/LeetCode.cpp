#include "leetcode/core.h"

namespace leetcode {
namespace problem_3080 {

using Func = std::function<vector<long long>(vector<int>&, vector<vector<int>>&)>;

class MarkElementsOnArrayByPerformingQueriesSolution : public SolutionBase<Func> {
 public:
  //! 3080. Mark Elements on Array by Performing Queries
  //! https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/
  vector<long long> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries);

  MarkElementsOnArrayByPerformingQueriesSolution();
};

}  // namespace problem_3080
}  // namespace leetcode
