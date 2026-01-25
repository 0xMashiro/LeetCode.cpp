#include "leetcode/core.h"

namespace leetcode {
namespace problem_1984 {

using Func = std::function<int(vector<int>&, int)>;

class MinimumDifferenceBetweenHighestAndLowestOfKScoresSolution : public SolutionBase<Func> {
 public:
  //! 1984. Minimum Difference Between Highest and Lowest of K Scores
  //! https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/
  int minimumDifference(vector<int>& nums, int k);

  MinimumDifferenceBetweenHighestAndLowestOfKScoresSolution();
};

}  // namespace problem_1984
}  // namespace leetcode