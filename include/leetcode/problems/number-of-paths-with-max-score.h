#ifndef LEETCODE_PROBLEMS_NUMBER_OF_PATHS_WITH_MAX_SCORE_H_
#define LEETCODE_PROBLEMS_NUMBER_OF_PATHS_WITH_MAX_SCORE_H_

#include "leetcode/core.h"

namespace leetcode {
namespace problem_1301 {

using Func = std::function<std::vector<int>(std::vector<std::string>&)>;

class NumberOfPathsWithMaxScoreSolution : public SolutionBase<Func> {
 public:
  //! 1301. Number of Paths with Max Score
  //! https://leetcode.com/problems/number-of-paths-with-max-score/
  std::vector<int> pathsWithMaxScore(std::vector<std::string>& board);

  NumberOfPathsWithMaxScoreSolution();
};

}  // namespace problem_1301
}  // namespace leetcode

#endif  // LEETCODE_PROBLEMS_NUMBER_OF_PATHS_WITH_MAX_SCORE_H_
