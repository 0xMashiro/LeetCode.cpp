#include "leetcode/core.h"

namespace leetcode {
namespace problem_2383 {

using Func = std::function<int(int, int, vector<int>&, vector<int>&)>;

class MinimumHoursOfTrainingToWinACompetitionSolution : public SolutionBase<Func> {
 public:
  //! 2383. Minimum Hours of Training to Win a Competition
  //! https://leetcode.com/problems/minimum-hours-of-training-to-win-a-competition/
  int minNumberOfHours(int initialEnergy, int initialExperience, 
                       vector<int>& energy, vector<int>& experience);

  MinimumHoursOfTrainingToWinACompetitionSolution();
};

}  // namespace problem_2383
}  // namespace leetcode
