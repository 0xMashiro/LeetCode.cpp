#include "leetcode/core.h"

namespace leetcode {
namespace problem_2416 {

using Func = std::function<vector<int>(vector<string>&)>;

class SumOfPrefixScoresOfStringsSolution : public SolutionBase<Func> {
 public:
  //! 2416. Sum of Prefix Scores of Strings
  //! https://leetcode.com/problems/sum-of-prefix-scores-of-strings/
  vector<int> sumPrefixScores(vector<string>& words);

  SumOfPrefixScoresOfStringsSolution();
};

}  // namespace problem_2416
}  // namespace leetcode
