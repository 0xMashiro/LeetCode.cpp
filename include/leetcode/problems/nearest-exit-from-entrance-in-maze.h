
#include "leetcode/core.h"

namespace leetcode {
namespace problem_1926 {

using Func = std::function<int(vector<vector<char>>&, vector<int>&)>;

class NearestExitFromEntranceInMazeSolution : public SolutionBase<Func> {
 public:
  //! 1926. Nearest Exit from Entrance in Maze
  //! https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/
  int nearestExit(vector<vector<char>>& maze, vector<int>& entrance);

  NearestExitFromEntranceInMazeSolution();
};

}  // namespace problem_1926
}  // namespace leetcode
