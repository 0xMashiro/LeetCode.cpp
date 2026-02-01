#include "leetcode/core.h"

namespace leetcode {
namespace problem_1203 {

using Func = std::function<vector<int>(int, int, vector<int>&, vector<vector<int>>&)>;

class SortItemsByGroupsRespectingDependenciesSolution : public SolutionBase<Func> {
 public:
  //! 1203. Sort Items by Groups Respecting Dependencies
  //! https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/
  vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems);

  SortItemsByGroupsRespectingDependenciesSolution();
};

}  // namespace problem_1203
}  // namespace leetcode
