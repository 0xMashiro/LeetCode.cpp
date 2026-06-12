#include "leetcode/core.h"

namespace leetcode {
namespace problem_1851 {

using Func = std::function<vector<int>(vector<vector<int>>&, vector<int>&)>;

class MinimumIntervalToIncludeEachQuerySolution : public SolutionBase<Func> {
 public:
  //! 1851. Minimum Interval to Include Each Query
  //! https://leetcode.com/problems/minimum-interval-to-include-each-query/
  vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries);

  MinimumIntervalToIncludeEachQuerySolution();
};

}  // namespace problem_1851
}  // namespace leetcode
