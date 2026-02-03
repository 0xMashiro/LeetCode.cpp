
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1992 {

using Func = std::function<vector<vector<int>>(vector<vector<int>>&)>;

class FindAllGroupsOfFarmlandSolution : public SolutionBase<Func> {
 public:
  //! 1992. Find All Groups of Farmland
  //! https://leetcode.com/problems/find-all-groups-of-farmland/
  vector<vector<int>> findFarmland(vector<vector<int>>& land);

  FindAllGroupsOfFarmlandSolution();
};

}  // namespace problem_1992
}  // namespace leetcode
