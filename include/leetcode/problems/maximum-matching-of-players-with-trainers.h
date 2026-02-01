#include "leetcode/core.h"

namespace leetcode {
namespace problem_2410 {

using Func = std::function<int(vector<int>&, vector<int>&)>;

class MaximumMatchingOfPlayersWithTrainersSolution : public SolutionBase<Func> {
 public:
  //! 2410. Maximum Matching of Players With Trainers
  //! https://leetcode.com/problems/maximum-matching-of-players-with-trainers/
  int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers);

  MaximumMatchingOfPlayersWithTrainersSolution();
};

}  // namespace problem_2410
}  // namespace leetcode
