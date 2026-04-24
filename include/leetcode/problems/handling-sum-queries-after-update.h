#include "leetcode/core.h"

namespace leetcode {
namespace problem_2569 {

using Func = std::function<vector<long long>(vector<int>&, vector<int>&, vector<vector<int>>&)>;

class HandlingSumQueriesAfterUpdateSolution : public SolutionBase<Func> {
 public:
  vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2,
                                 vector<vector<int>>& queries);

  HandlingSumQueriesAfterUpdateSolution();
};

}  // namespace problem_2569
}  // namespace leetcode
