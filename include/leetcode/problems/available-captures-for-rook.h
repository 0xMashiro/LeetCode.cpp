
#include "leetcode/core.h"

namespace leetcode {
namespace problem_999 {

using Func = std::function<int(vector<vector<char>>&)>;

class AvailableCapturesForRookSolution : public SolutionBase<Func> {
 public:
  //! 999. Available Captures for Rook
  //! https://leetcode.com/problems/available-captures-for-rook/
  int numRookCaptures(vector<vector<char>>& board);

  AvailableCapturesForRookSolution();
};

}  // namespace problem_999
}  // namespace leetcode
