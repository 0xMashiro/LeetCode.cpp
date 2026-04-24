#include "leetcode/core.h"

namespace leetcode {
namespace problem_2223 {

using Func = std::function<long(string)>;

class SumOfScoresOfBuiltStringsSolution : public SolutionBase<Func> {
 public:
  //! 2223. Sum of Scores of Built Strings
  //! https://leetcode.com/problems/sum-of-scores-of-built-strings/
  long sumScores(string s);

  SumOfScoresOfBuiltStringsSolution();
};

}  // namespace problem_2223
}  // namespace leetcode
