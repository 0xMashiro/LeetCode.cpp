
#include "leetcode/core.h"

namespace leetcode {
namespace problem_2954 {

using Func = std::function<int(int, vector<int>&)>;

class CountTheNumberOfInfectionSequencesSolution : public SolutionBase<Func> {
 public:
  //! 2954. Count the Number of Infection Sequences
  //! https://leetcode.com/problems/count-the-number-of-infection-sequences/
  int numberOfSequence(int n, vector<int>& sick);

  CountTheNumberOfInfectionSequencesSolution();
};

}  // namespace problem_2954
}  // namespace leetcode
