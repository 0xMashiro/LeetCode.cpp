#include "leetcode/core.h"

namespace leetcode {
namespace problem_3175 {

using Func = std::function<int(vector<int>&, int)>;

class FindTheFirstPlayerToWinKGamesInARowSolution : public SolutionBase<Func> {
 public:
  int findWinningPlayer(vector<int>& skills, int k);
  FindTheFirstPlayerToWinKGamesInARowSolution();
};

}  // namespace problem_3175
}  // namespace leetcode
