#include "leetcode/core.h"

namespace leetcode {
namespace problem_3771 {

using Func = std::function<long long(int, vector<int>&, vector<int>&)>;

class TotalScoreOfDungeonRunsSolution : public SolutionBase<Func> {
 public:
  //! 3771. Total Score of Dungeon Runs
  //! https://leetcode.com/problems/total-score-of-dungeon-runs/
  long long totalScore(int hp, vector<int>& damage, vector<int>& requirement);

  TotalScoreOfDungeonRunsSolution();
};

}  // namespace problem_3771
}  // namespace leetcode
