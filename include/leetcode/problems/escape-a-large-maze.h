#include "leetcode/core.h"

namespace leetcode {
namespace problem_1036 {

using Func = std::function<bool(vector<vector<int>>&, vector<int>&, vector<int>&)>;

class EscapeALargeMazeSolution : public SolutionBase<Func> {
 public:
  //! 1036. Escape a Large Maze
  //! https://leetcode.com/problems/escape-a-large-maze/
  bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source,
                        vector<int>& target);

  EscapeALargeMazeSolution();
};

}  // namespace problem_1036
}  // namespace leetcode
